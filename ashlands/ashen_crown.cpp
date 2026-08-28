#include <algorithm>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string RESET = "\033[0m", BOLD = "\033[1m", DIM = "\033[2m";
const string RED = "\033[31m", GREEN = "\033[32m", YELLOW = "\033[33m";
const string CYAN = "\033[36m", MAGENTA = "\033[35m", WHITE = "\033[97m";
const string SAVE_FILE = "ashen_crown.save";

struct Enemy { string name, glyph; int hp, maxHp, attack, gold, xp; bool boss = false; };
struct Player {
	string name = "Aster";
	int hp = 42, maxHp = 42, mana = 14, maxMana = 14, attack = 8, defense = 3;
	int gold = 25, xp = 0, level = 1, potions = 3, ethers = 1, bombs = 0;
	int weapon = 0, armor = 0, relics = 0, steps = 0;
	int questKills = 0, keys = 0;
	bool questActive = false, questComplete = false, ward = false, finalBoss = false;
	bool dungeonCleared = false;
};

mt19937 rng(static_cast<unsigned>(chrono::steady_clock::now().time_since_epoch().count()));
int roll(int low, int high) { return uniform_int_distribution<int>(low, high)(rng); }
void clearScreen() { cout << "\033[2J\033[H"; }
void pauseGame() { cout << DIM << "\nPress ENTER to continue..." << RESET; string line; getline(cin, line); }
void title(const string& text) { cout << "\n" << CYAN << BOLD << "== " << text << " ==" << RESET << "\n"; }
void bar(int value, int maximum, int width, const string& color) {
	int filled = maximum ? max(0, min(width, value * width / maximum)) : 0;
	cout << color << "[" << string(filled, '#') << string(width - filled, '-') << "]" << RESET;
}
void banner() {
	cout << MAGENTA << BOLD
		 << "      .       *        .       *       .\n"
		 << "  /\\_/\\   THE ASHEN CROWN   /\\_/\\\n"
		 << " ( o.o )  terminal fantasy RPG  ( o.o )\n"
		 << "  > ^ <                         > ^ <\n" << RESET;
}
string weaponName(int weapon) { return weapon == 0 ? "Rusty blade" : weapon == 1 ? "Embersteel" : weapon == 2 ? "Star-forged edge" : "Crownfang"; }
string armorName(int armor) { return armor == 0 ? "Traveler's coat" : armor == 1 ? "Ashplate" : "Wyrmguard mail"; }
void status(const Player& p) {
	cout << WHITE << BOLD << p.name << RESET << "  " << YELLOW << "Lv " << p.level << RESET
		 << "  HP "; bar(p.hp, p.maxHp, 16, GREEN); cout << " " << p.hp << "/" << p.maxHp
		 << "  MP "; bar(p.mana, p.maxMana, 10, CYAN); cout << " " << p.mana << "/" << p.maxMana
		 << "  " << YELLOW << p.gold << "g" << RESET << "\n";
}
int worldValue(int seed, int x, int y) { unsigned n = static_cast<unsigned>(seed) ^ (x * 374761393u) ^ (y * 668265263u); n = (n ^ (n >> 13)) * 1274126177u; return static_cast<int>((n ^ (n >> 16)) % 100); }
char terrain(int seed, int x, int y) {
	int n = worldValue(seed, x, y);
	if (n < 12) return '~';
	if (n < 25) return '^';
	if (n < 38) return ':';
	if (n < 48) return '"';
	return '.';
}
string coloredTerrain(char tile) {
	if (tile == '~') return CYAN + string("~") + RESET;
	if (tile == '^') return WHITE + string("^") + RESET;
	if (tile == ':') return YELLOW + string(":") + RESET;
	if (tile == '"') return GREEN + string("\"") + RESET;
	return DIM + string(".") + RESET;
}
string landmark(int x, int y, const Player& p) {
	if (x == 2 && y == 2) return YELLOW + string("T") + RESET;
	if (x == 9 && y == 8) return YELLOW + string("T") + RESET;
	if (x == 1 && y == 10) return GREEN + string("H") + RESET;
	if (x == 8 && y == 8) return MAGENTA + string("D") + RESET;
	if (x == 10 && y == 1) return RED + string("B") + RESET;
	if (x == 10 && y == 10) return RED + string("B") + RESET;
	if (x == 1 && y == 1) return RED + string("B") + RESET;
	if (x == 6 && y == 6 && p.relics == 4) return YELLOW + string("C") + RESET;
	return "";
}
void drawMap(int seed, int px, int py, const Player& p) {
	cout << "\n" << DIM << "World seed: " << seed << "     0 1 2 3 4 5 6 7 8 9 A B\n    ";
	for (int y = 0; y < 12; ++y) {
		cout << (y < 10 ? " " : "") << y << "  ";
		for (int x = 0; x < 12; ++x) {
			if (x == px && y == py) cout << CYAN << BOLD << "@ " << RESET;
			else if (x == 0 || y == 0 || x == 11 || y == 11) cout << DIM << "# " << RESET;
			else { string mark = landmark(x, y, p); cout << (mark.empty() ? coloredTerrain(terrain(seed, x, y)) : mark) << " "; }
		}
		cout << "\n    ";
	}
	cout << RESET << "\n" << DIM << "@ you  T town/shop  H shrine  B area boss  D dungeon  C Crown of Dawn\n"
		 << "~ water  ^ mountain  : ruins  \" forest  . ashland\n" << RESET;
}

Enemy enemyAt(int x, int y, int seed, int level) {
	int balancedLevel = min(12, max(1, level + (worldValue(seed + 91, x, y) % 3) - 1));
	if (x == 8 && y == 8) return {"THE HOLLOW ARCHON", "A", 105 + level * 4, 105 + level * 4, 17 + level, 125, 170, true};
	if ((x == 1 && y == 1) || (x == 10 && y == 1) || (x == 10 && y == 10)) {
		int tier = (x == 1 && y == 1) ? 1 : (x == 10 && y == 1) ? 2 : 3;
		if (tier == 1) return {"THE BONE COLOSSUS", "X", 58 + level * 2, 58 + level * 2, 10 + level, 55, 75, true};
		if (tier == 2) return {"THE CINDER WYRM", "W", 90 + level * 3, 90 + level * 3, 14 + level, 90, 125, true};
		return {"THE STARVED EMPEROR", "E", 125 + level * 4, 125 + level * 4, 18 + level, 140, 190, true};
	}
	int n = worldValue(seed + balancedLevel * 31, x, y) % 4;
	if (n == 0) return {"Moss Goblin", "g", 20 + balancedLevel * 2, 20 + balancedLevel * 2, 5 + balancedLevel, 9 + balancedLevel, 20 + balancedLevel * 2};
	if (n == 1) return {"Grave Wisp", "w", 25 + balancedLevel * 2, 25 + balancedLevel * 2, 7 + balancedLevel, 13 + balancedLevel, 28 + balancedLevel * 2};
	if (n == 2) return {"Ash Wolf", "v", 23 + balancedLevel * 2, 23 + balancedLevel * 2, 8 + balancedLevel, 11 + balancedLevel, 25 + balancedLevel * 2};
	return {"Ruin Knight", "/", 32 + balancedLevel * 3, 32 + balancedLevel * 3, 10 + balancedLevel, 18 + balancedLevel * 2, 38 + balancedLevel * 3};
}
int travelCost(int seed, int x, int y) {
	char tile = terrain(seed, x, y);
	return tile == '^' || tile == ':' ? 2 : 1;
}
void levelUp(Player& p) {
	while (p.xp >= p.level * 55) {
		p.xp -= p.level * 55; ++p.level; p.maxHp += 9; p.maxMana += 3; p.attack += 2; p.defense += 1; p.hp = p.maxHp; p.mana = p.maxMana;
		cout << YELLOW << BOLD << "LEVEL UP! You reached level " << p.level << ".\n" << RESET;
	}
}
bool combat(Player& p, Enemy foe) {
	clearScreen(); title("BATTLE: " + foe.name); cout << RED << "A hostile shape rises from the ash!" << RESET << "\n";
	while (p.hp > 0 && foe.hp > 0) {
		status(p); cout << RED << foe.name << RESET << "  "; bar(foe.hp, foe.maxHp, 24, RED); cout << " " << foe.hp << "/" << foe.maxHp << "\n\n";
		cout << "[1] Strike  [2] Ember spell (4 MP)  [3] Potion (" << p.potions << ")  [4] Ether (" << p.ethers << ")\n[5] Bomb (" << p.bombs << ")  [6] Defend  [7] Flee\n> ";
		string cmd; getline(cin, cmd); int damage = 0; bool defending = false;
		if (cmd == "1" || cmd == "attack" || cmd == "strike") { damage = max(1, p.attack + roll(-2, 4)); if (roll(1, 100) <= 12) { damage *= 2; cout << YELLOW << BOLD << "CRITICAL HIT! " << RESET; } cout << YELLOW << "Your " << weaponName(p.weapon) << " deals " << damage << ".\n" << RESET; }
		else if (cmd == "2" || cmd == "spell") { if (p.mana < 4) { cout << "Not enough mana.\n"; continue; } p.mana -= 4; damage = roll(10, 18) + p.level; cout << CYAN << "Blue fire crashes down for " << damage << ".\n" << RESET; }
		else if (cmd == "3" || cmd == "potion") { if (!p.potions) { cout << "Your satchel is empty.\n"; continue; } --p.potions; p.hp = min(p.maxHp, p.hp + 22); cout << GREEN << "Warm light restores your wounds.\n" << RESET; }
		else if (cmd == "4" || cmd == "ether") { if (!p.ethers) { cout << "No ether remains.\n"; continue; } --p.ethers; p.mana = min(p.maxMana, p.mana + 10); cout << CYAN << "Your mana surges back.\n" << RESET; }
		else if (cmd == "5" || cmd == "bomb") { if (!p.bombs) { cout << "No bombs remain.\n"; continue; } --p.bombs; damage = roll(22, 35); cout << MAGENTA << "The bomb tears through the arena for " << damage << ".\n" << RESET; }
		else if (cmd == "6" || cmd == "defend") { defending = true; cout << CYAN << "You brace behind your guard. Incoming damage is halved.\n" << RESET; }
		else if (cmd == "7" || cmd == "flee") { if (foe.boss || roll(1, 3) != 1) cout << "The enemy blocks your escape!\n"; else { cout << "You vanish into smoke.\n"; return false; } }
		else { cout << "Choose an action.\n"; continue; }
		foe.hp -= damage;
		if (foe.hp > 0) { int hit = max(0, foe.attack + roll(-2, 2) - p.defense); if (p.ward) { hit /= 2; p.ward = false; cout << CYAN << "Your shrine ward flashes.\n" << RESET; } if (defending) hit /= 2; p.hp -= hit; cout << RED << foe.name << " hits for " << hit << ".\n" << RESET; }
		if (p.hp > 0) pauseGame();
	}
	if (p.hp <= 0) { cout << RED << "Your vision fades into ember-black...\n" << RESET; return false; }
	p.gold += foe.gold; p.xp += foe.xp; if (!foe.boss && p.questActive && !p.questComplete) ++p.questKills; if (foe.boss) { ++p.relics; ++p.keys; }
	if (!foe.boss && roll(1, 100) <= 22) { if (roll(1, 2) == 1) { ++p.potions; cout << GREEN << "The enemy dropped a potion.\n" << RESET; } else { ++p.bombs; cout << MAGENTA << "The enemy dropped a fire bomb.\n" << RESET; } }
	cout << GREEN << "Victory! +" << foe.gold << " gold, +" << foe.xp << " XP" << (foe.boss ? ", relic claimed!" : "") << ".\n" << RESET; levelUp(p); pauseGame(); return true;
}
void questBoard(Player& p) {
	clearScreen(); title("THE BOUNTY BOARD");
	if (p.questComplete) { cout << GREEN << "Bounty complete: the board owes you nothing more today.\n" << RESET; pauseGame(); return; }
	if (!p.questActive) { p.questActive = true; p.questKills = 0; cout << YELLOW << "New bounty: defeat 5 creatures in the wild. Reward: 75 gold and 60 XP.\n" << RESET; pauseGame(); return; }
	cout << "Bounty progress: " << p.questKills << "/5 creatures defeated.\n";
	if (p.questKills >= 5) { p.questActive = false; p.questComplete = true; p.gold += 75; p.xp += 60; levelUp(p); cout << GREEN << BOLD << "Bounty claimed! +75 gold, +60 XP.\n" << RESET; }
	else cout << DIM << "Return after hunting more creatures.\n" << RESET;
	pauseGame();
}
void shop(Player& p) {
	while (true) {
		clearScreen(); title("EMBERFALL AUTOMATIC SHOP"); status(p);
		cout << "The brass vendor restocks itself whenever the bell rings.\n\n"
			 << "[1] Potion +1       8g\n[2] Ether +1        12g\n[3] Fire bomb +1     18g\n"
			 << "[4] Embersteel      45g  (" << (p.weapon >= 1 ? "owned" : "+5 attack") << ")\n"
			 << "[5] Ashplate        50g  (" << (p.armor >= 1 ? "owned" : "+4 defense") << ")\n[6] Bounty board\n[7] Leave\n> ";
		string cmd; getline(cin, cmd);
		if (cmd == "1" && p.gold >= 8) { p.gold -= 8; ++p.potions; }
		else if (cmd == "2" && p.gold >= 12) { p.gold -= 12; ++p.ethers; }
		else if (cmd == "3" && p.gold >= 18) { p.gold -= 18; ++p.bombs; }
		else if (cmd == "4" && p.weapon < 1 && p.gold >= 45) { p.gold -= 45; p.weapon = 1; p.attack += 5; cout << YELLOW << "Embersteel hums. Attack +5.\n" << RESET; pauseGame(); }
		else if (cmd == "5" && p.armor < 1 && p.gold >= 50) { p.gold -= 50; p.armor = 1; p.defense += 4; cout << CYAN << "Ashplate locks into place. Defense +4.\n" << RESET; pauseGame(); }
		else if (cmd == "6") questBoard(p);
		else if (cmd == "7" || cmd == "leave") return;
		else { cout << RED << "Not enough gold, or that item is already yours.\n" << RESET; pauseGame(); }
	}
}
void town(Player& p) {
	while (true) {
		clearScreen(); title("TOWN COMMONS"); status(p);
		cout << "Travelers trade rumors beneath a canvas roof.\n\n"
			 << "[1] Automatic shop\n[2] Bounty board\n[3] Inn (10g, full restore)\n[4] Leave\n> ";
		string cmd; getline(cin, cmd);
		if (cmd == "1" || cmd == "shop") shop(p);
		else if (cmd == "2" || cmd == "bounty") questBoard(p);
		else if (cmd == "3" && p.gold >= 10) { p.gold -= 10; p.hp = p.maxHp; p.mana = p.maxMana; cout << GREEN << "The inn restores every scar.\n" << RESET; pauseGame(); }
		else if (cmd == "4" || cmd == "leave") return;
		else { cout << RED << "The inn costs 10 gold.\n" << RESET; pauseGame(); }
	}
}
void shrine(Player& p) { clearScreen(); title("THE QUIET SHRINE"); p.hp = p.maxHp; p.mana = p.maxMana; p.ward = true; cout << "Silver rain falls upward.\n" << CYAN << "You are restored. A ward will soften one incoming strike.\n" << RESET; pauseGame(); }
void inspect(const Player& p) { clearScreen(); title("CHARACTER"); status(p); cout << "Attack: " << p.attack << "  Defense: " << p.defense << "  XP: " << p.xp << "/" << p.level * 55 << "\nWeapon: " << weaponName(p.weapon) << "\nArmor: " << armorName(p.armor) << "\nRelics: " << p.relics << "/4  Keys: " << p.keys << "\nItems: " << p.potions << " potions, " << p.ethers << " ethers, " << p.bombs << " bombs\nBounty: " << (p.questComplete ? "complete" : p.questActive ? to_string(p.questKills) + "/5" : "not accepted") << "\nSteps: " << p.steps << "\n"; pauseGame(); }

bool saveGame(const Player& p, int seed, int x, int y, const bool defeated[3], bool quiet = false) {
	ofstream out(SAVE_FILE, ios::trunc); if (!out) return false;
	out << "ASHEN_CROWN_V4\n" << p.name << '\n' << seed << ' ' << x << ' ' << y << '\n'
		<< p.hp << ' ' << p.maxHp << ' ' << p.mana << ' ' << p.maxMana << ' ' << p.attack << ' ' << p.defense << ' '
		<< p.gold << ' ' << p.xp << ' ' << p.level << ' ' << p.potions << ' ' << p.ethers << ' ' << p.bombs << ' '
		<< p.weapon << ' ' << p.armor << ' ' << p.relics << ' ' << p.steps << ' ' << p.questKills << ' ' << p.keys << ' '
		<< p.questActive << ' ' << p.questComplete << ' ' << p.dungeonCleared << ' ' << p.ward << ' ' << p.finalBoss << '\n'
		<< defeated[0] << ' ' << defeated[1] << ' ' << defeated[2] << '\n';
	if (!quiet) cout << GREEN << "Game saved to ashlands/ashen_crown.save.\n" << RESET;
	return true;
}
bool loadGame(Player& p, int& seed, int& x, int& y, bool defeated[3]) {
	ifstream in(SAVE_FILE); string version; if (!(in >> version) || version != "ASHEN_CROWN_V4") return false;
	in >> ws; getline(in, p.name);
	if (!(in >> seed >> x >> y >> p.hp >> p.maxHp >> p.mana >> p.maxMana >> p.attack >> p.defense >> p.gold >> p.xp >> p.level >> p.potions >> p.ethers >> p.bombs >> p.weapon >> p.armor >> p.relics >> p.steps >> p.questKills >> p.keys >> p.questActive >> p.questComplete >> p.dungeonCleared >> p.ward >> p.finalBoss >> defeated[0] >> defeated[1] >> defeated[2])) return false;
	return !p.name.empty() && p.hp > 0 && p.maxHp > 0 && p.mana >= 0 && p.maxMana > 0 && p.level > 0 && x > 0 && x < 11 && y > 0 && y < 11 && p.relics >= 0 && p.relics <= 3;
}
bool deleteSave() { return remove(SAVE_FILE.c_str()) == 0; }
bool titleScreen(Player& p, int& seed, int& x, int& y, bool defeated[3]) {
	while (true) {
		clearScreen(); banner(); cout << "\n" << WHITE << "The sun died three winters ago. Three relics can relight it.\n" << RESET
			<< "[1] New expedition\n[2] Resume expedition " << (ifstream(SAVE_FILE) ? "(save found)" : "(no save)") << "\n[3] Delete save\n[4] Quit\n> ";
		string choice; getline(cin, choice);
		if (choice == "1" || choice == "new") { p = Player(); seed = roll(10000, 999999); x = y = 6; defeated[0] = defeated[1] = defeated[2] = false; cout << "\nHero name (ENTER for Aster): "; getline(cin, p.name); if (p.name.empty()) p.name = "Aster"; saveGame(p, seed, x, y, defeated, true); return true; }
		if (choice == "2" || choice == "resume") { if (loadGame(p, seed, x, y, defeated)) { cout << GREEN << "Save restored.\n" << RESET; pauseGame(); return true; } cout << RED << "No valid save found.\n" << RESET; pauseGame(); }
		else if (choice == "3" || choice == "delete") { cout << (deleteSave() ? GREEN + string("Save deleted.\n") + RESET : YELLOW + string("There is no save to delete.\n") + RESET); pauseGame(); }
		else if (choice == "4" || choice == "quit" || choice == "q") return false;
	}
}
int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	Player player; int seed = 0, x = 6, y = 6; bool defeated[3] = {false, false, false};
	if (!titleScreen(player, seed, x, y, defeated)) return 0;
	while (true) {
		if (player.hp <= 0) { clearScreen(); banner(); cout << RED << BOLD << "THE ASHLANDS CLAIM YOU\n" << RESET << "[1] Rise again (lose carried loot)  [2] Quit\n> "; string death; getline(cin, death); if (death == "1") { player.hp = player.maxHp; player.mana = player.maxMana; player.gold /= 2; x = y = 6; continue; } break; }
		clearScreen(); banner(); status(player); drawMap(seed, x, y, player);
		cout << "\n" << WHITE << "Command [n/s/e/w, map, stats, save, shop, menu, help, quit]" << RESET << "\n> "; string input; getline(cin, input);
		if (input == "quit" || input == "q") break;
		if (input == "help") { cout << "Move with WASD or north/south/east/west. Water (~) is impassable; mountains (^) and ruins (:) cost 2 steps. Landmarks: T shop, H shrine, B boss. Reach C after all three relics.\n"; pauseGame(); continue; }
		if (input == "map" || input == "stats") { if (input == "stats") inspect(player); else pauseGame(); continue; }
		if (input == "save") { saveGame(player, seed, x, y, defeated); pauseGame(); continue; }
		if (input == "shop") { if ((x == 2 && y == 2) || (x == 9 && y == 8)) shop(player); else { cout << "The automatic shop is in a town (T).\n"; pauseGame(); } continue; }
		if (input == "menu") { saveGame(player, seed, x, y, defeated, true); if (!titleScreen(player, seed, x, y, defeated)) break; continue; }
		int nx = x, ny = y; if (input == "n" || input == "north" || input == "w") --ny; if (input == "s" || input == "south" || input == "x") ++ny; if (input == "e" || input == "east" || input == "d") ++nx; if (input == "west" || input == "a") --nx;
		if (nx == x && ny == y) { cout << "The ash does not understand that command.\n"; pauseGame(); continue; }
		if (nx <= 0 || nx >= 11 || ny <= 0 || ny >= 11) { cout << "A cliff of black glass blocks the way.\n"; pauseGame(); continue; }
		if (terrain(seed, nx, ny) == '~' && nx != 2 && ny != 2) { cout << CYAN << "Deep water blocks the route.\n" << RESET; pauseGame(); continue; }
		if (nx == 10 && ny == 1 && player.keys < 1) { cout << RED << "A rune gate demands the Colossus Key.\n" << RESET; pauseGame(); continue; }
		if (nx == 10 && ny == 10 && player.keys < 2) { cout << RED << "Two rune gates seal the Emperor's road.\n" << RESET; pauseGame(); continue; }
		if (nx == 8 && ny == 8 && player.relics < 1) { cout << MAGENTA << "The dungeon door needs a Dawn relic to open.\n" << RESET; pauseGame(); continue; }
		x = nx; y = ny; player.steps += travelCost(seed, x, y); saveGame(player, seed, x, y, defeated, true);
		if ((x == 2 && y == 2) || (x == 9 && y == 8)) town(player);
		else if (x == 1 && y == 10) shrine(player);
		else if (x == 8 && y == 8) {
			if (!player.dungeonCleared) { if (combat(player, enemyAt(x, y, seed, player.level))) player.dungeonCleared = true; saveGame(player, seed, x, y, defeated, true); }
			else { cout << DIM << "The Archon's dungeon is silent.\n" << RESET; pauseGame(); }
		}
		else if ((x == 1 && y == 1) || (x == 10 && y == 1) || (x == 10 && y == 10)) {
			int boss = (x == 1 && y == 1) ? 0 : (x == 10 && y == 1) ? 1 : 2;
			if (!defeated[boss]) { if (combat(player, enemyAt(x, y, seed, player.level))) defeated[boss] = true; saveGame(player, seed, x, y, defeated, true); }
			else { cout << DIM << "The defeated boss's arena is silent.\n" << RESET; pauseGame(); }
		} else if (x == 6 && y == 6 && player.relics == 4) { clearScreen(); banner(); cout << YELLOW << BOLD << "THE CROWN REMEMBERS THE SUN\n\n" << RESET << "Dawn pours across the terminal. Your expedition is complete.\n"; break; }
		else if (roll(1, 100) <= 28) combat(player, enemyAt(x, y, seed, player.level));
		else cout << DIM << "Only ash, shifting terrain, and distant thunder.\n" << RESET;
	}
	saveGame(player, seed, x, y, defeated, true); cout << "\n" << MAGENTA << "Thanks for playing THE ASHEN CROWN.\n" << RESET; return 0;
}
