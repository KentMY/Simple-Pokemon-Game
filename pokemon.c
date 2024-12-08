#include <stdio.h>
#include <math.h> // for pow() and the formula for leveling
#include <stdlib.h> // for rand() and some things
#include <string.h> // for string manipulations
#include <unistd.h> // for sleep()
#include <time.h> // for random numbers to be randomize more than once.
#include <conio.h> // if getch() doesn't work include this

/*/
 * Simple Pokemon Game
 * This game only lets the player use 1 pokemon for the entirety of the game.
 * Though, this is just a short game.
 * -- Each increase of level grants 10 HP.
 * -- In every battle, the opponent will always move first.
/*/

// global variables:

int candy = 0, outfit1 = 0, outfit2 = 0, outfit3 = 0;
int money = 0, choice, action, pokemonChoice, theEnd = 0;
int pokemonLevel = 1, pokemonExp = 0, pokemonHP, pokemonMaxHP = 100, evolved = 0, evolvedAgain = 0;
// for pokedex:
int charmander = 0, charmeleon = 0, charizard = 0, bulbasaur = 0, ivysaur = 0, venusaur = 0, squirtle = 0, wartortle = 0, blastoise = 0, pikachu = 0, magikarp = 0,  rapidash = 0, mewtwo = 0;
char starterPokemon[20];
char name[11], outfit[30] = "Casual";
char confirm;
char *moveset[] = {"Tackle", "Scratch", "Spit", "Dirt Throw"};
int movePower[] = {10, 10, 10, 10};

// Function declarations:

void clearBuffer();
void wipe();
void evolution();
void evoAndLevel();
void adventure(); //
void venture(); // random encounters or bonuses
int training(int level); // get exp based on 5% to 10% of exp cap
void gymBattle();
void battleCrissa();
void battleSheba();
void battleRival();
void pokedex();
void pokeMart();
void profile();
void pokeCenter();
int levelingFormula(int N); // formula for the exp cap 
void showMoves();
void displayHP(int currentHP, int maxHP);

int main() {
    pokemonHP = pokemonMaxHP; // initial value of starter pokemon HP
    srand(time(0)); // to seed(not the sus one) random numbers

    printf("Enter name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // exception handling to consume newline

    printf("\nHello %s! Your adventure will start now\n", name);
    getch();
    wipe();
    puts(" Prof. Oak: Welcome to the World of Pokemon!\n");
    getch();
    puts(" Prof. Oak: In this perilous world, evil run rampant. But a pokemon will help you tread through safely.\n");
    getch();
    puts(" Prof. Oak: Therefore, I will hand you one of these three that I wish you foster.\n");
    printf("\n  ======================\n");
    puts("\n  ‡‡ [1] - Charmander ‡‡");
    puts("\n  ‡‡ [2] - Bulbasaur  ‡‡");
    puts("\n  ‡‡ [3] - Squirtle   ‡‡\n");
    printf("  ======================\n\n");
    printf("\n Prof. Oak: So which one have you taken a liken to? ");
    if (scanf("%d", &pokemonChoice) != 1) {
        while (getchar() != '\n');
    }

    switch (pokemonChoice) {
        case 1:
            charmander = 1;
            // below is an assignment of value to the string starterPokemon
            snprintf(starterPokemon, sizeof(starterPokemon), "Charmander");
            puts("\nProf. Oak: Oh, a Charmander, is it? A nice pick.\n");
            moveset[1] = "Ember";
            movePower[1] = 40;
            break;
        case 2:
            bulbasaur = 1;
            snprintf(starterPokemon, sizeof(starterPokemon), "Bulbasaur");
            puts("\nProf. Oak: Bulbasaur? A cute vegetable, not bad.\n");
            moveset[1] = "Vine Whip";
            movePower[1] = 45;
            break;
        case 3:
            squirtle = 1;
            snprintf(starterPokemon, sizeof(starterPokemon), "Squirtle");
            puts("\nProf. Oak: Squirtle, huh. Very well\n");
            moveset[1] = "Water Gun";
            movePower[1] = 40;
            break;
        default: // game defaults to Pikachu with a complete moveset
            pikachu = 1;
            snprintf(starterPokemon, sizeof(starterPokemon), "Pikachu");
            puts("\nProf. Oak: Well, that is not part of the choice, but i'll give you a Pikachu\n");
            moveset[0] = "Swift";
            moveset[1] = "Spark";
            moveset[2] = "Thunderbolt";
            moveset[3] = "Iron Tail";
            movePower[0] = 60;
            movePower[1] = 65;
            movePower[2] = 90;
            movePower[3] = 100;
            break;
    }
    getch();
    printf("Prof. Oak: Additionally, have this 10 candies to help you on the way. Each candy can level up your pokemon.\n");
    candy += 10;
    getch();
    printf("\nProf. Oak: Now go forth and venture this world with your companion %s\n", starterPokemon);
    getch();
    wipe();

    do {
        evoAndLevel();

        printf(" ************************************************\n");
        puts("\n ** [1] Adventure  - Go on an adventure        **");
        puts("\n ** [2] Pokedex    - Read some pokemon entries **");
        puts("\n ** [3] PokeMart   - Browse some products      **");
        puts("\n ** [4] Profile    - Look in the mirror        **");
        puts("\n ** [5] PokeCenter - Heal your pokemon here    **");
        if (theEnd == 1) { // if the player wins against the Rival, this will appear
            puts("\n ** [6] The End    - End the Game              **");
        }
        printf("\n ************************************************\n");
        printf("\n Enter action: ");
        if (scanf("%d", &action) != 1) {
            while(getchar() != '\n');
        }

        if (action == 1) {
            adventure();
        } else if (action == 2) {
            pokedex();
        } else if (action == 3) {
            pokeMart();
        } else if (action == 4) {
            profile();
        } else if (action == 5) {
            pokeCenter();
        } else if (action == 6 && theEnd == 1) {
            wipe();
            printf("\n Congrats on beating this short of a game. Hope you enjoyed whatever little it offered!");
            break;
        } else {
            printf("\n Invalid input. Please repeat");
            getch();
            wipe();
        }
    } while (1);
    return 0;
}

void clearBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void wipe() {
    // printf("\033[H\033[J"); // include if below doesn't work
    system("clear"); // "clear" if "cls" doesn't work.
}

void evolution() { // this function gets the name of the next evolution of your chosen pokemon
    if (pokemonLevel == 4) {
        if (pokemonChoice == 1) {
            snprintf(starterPokemon, sizeof(starterPokemon), "Charmeleon");
            charmeleon = 1;
        } else if (pokemonChoice == 2) {
            snprintf(starterPokemon, sizeof(starterPokemon), "Ivysaur");
            ivysaur = 1;
        } else if (pokemonChoice == 3) {
            snprintf(starterPokemon, sizeof(starterPokemon), "Wartortle");
            wartortle = 1;
        }
    }
    
    if (pokemonLevel == 8) {
        if (pokemonChoice == 1) {
            snprintf(starterPokemon, sizeof(starterPokemon), "Charizard");
            charizard = 1;
        } else if (pokemonChoice == 2) {
            snprintf(starterPokemon, sizeof(starterPokemon), "Venusaur");
            venusaur = 1;
        } else if (pokemonChoice == 3) {
            snprintf(starterPokemon, sizeof(starterPokemon), "Blastoise");
            blastoise = 1;
        }
    }
}

void evoAndLevel() {
    while (pokemonExp >= levelingFormula(pokemonLevel)) { // Handle evolutions and leveling
        pokemonExp = 0;
        pokemonLevel++;
        pokemonMaxHP += 20;
        pokemonHP = pokemonMaxHP;
        printf("Your %s leveled up!\n", starterPokemon);
        getch();
        wipe();
        }
    // this part adds new moves to your pokemon at level 8, 16, and 20
    if (pokemonLevel == 8 ) {
        if (pokemonChoice == 1) {
            moveset[2] = "Dragon Fang";
            movePower[2] = 60;
        } else if (pokemonChoice == 2) {
            moveset[2] = "Razor Leaf";
            movePower[2] = 55;
        } else if (pokemonChoice == 3) {
            moveset[2] = "Water Pulse";
            movePower[2] = 60;
        }
    } else if (pokemonLevel == 16) {
        if (pokemonChoice == 1) {
            moveset[3] = "Inferno";
            movePower[3] = 90;
        } else if (pokemonChoice == 2) {
            moveset[3] = "Seed Bomb";
            movePower[3] = 80;
        } else if (pokemonChoice == 3) {
            moveset[3] = "Aqua Tail";
            movePower[3] = 90;
        }
    } else if (pokemonLevel == 20) {
        if (pokemonChoice == 1) {
            moveset[0] = "Flare Blitz";
            movePower[0] = 120;
        } else if (pokemonChoice == 2) {
            moveset[0] = "Solar Beam";
            movePower[0] = 120;
        } else if (pokemonChoice == 3) {
            moveset[0] = "Wave Crash";
            movePower[0] = 120;
        }
        printf("\n Your %s learned a new move %s for reaching level 20!", starterPokemon, moveset[0]);
    }
    // this part handles the evolution dialogue
    if (pokemonLevel == 4 && evolved == 0) {
        printf("\n (**) Hold on\n");
        sleep(2);
        printf("\n (**) There is omething happening to your %s, it seems to be glowing in such resplendent light!\n", starterPokemon);
        sleep(3);
        printf("\n \\(OO)/ Oh what's this? It's actually evolving!\n");
        sleep(3);
        printf("\n \\(OO)/ Your %s evolved into ", starterPokemon);
        evolution();
        printf("%s!\n", starterPokemon);
        evolved = 1;
        printf("\n Press any key to continue...");
        getch();
        wipe();
    } else if (pokemonLevel == 8 && evolvedAgain == 0) {
        printf("\n \\(OO)/ Oh damn! Your %s is glowing again!\n", starterPokemon);
        sleep(2);
        printf("\n \\(OO)/ Color me surprise! This glow is even brighter than its previous evolution, is this perhaps its final evolution?\n");
        sleep(3);
        printf("\n (OO) *zzziing* Your %s evolved into ", starterPokemon);
        evolution();
        printf("\n %s!\n", starterPokemon);
        evolvedAgain = 1;
        getch();
        wipe();
    }
}

void adventure() {
    wipe();
    int opponentChoice, trainingExp;

    printf("\n^^ [1] Embark on a journey with your %s and take a step into the world of adventure.\n", starterPokemon);
    printf("\n^^ [2] Train your %s\n", starterPokemon);
    printf("\n^^ [3] Gym Battle\n");
    printf("\n Enter action: ");
    if (scanf("%d", &action) != 1) {
        while(getchar() != '\n');
        wipe();
        return;
    }

    if (action == 1) {
        venture();
    } else if (action == 2) {
        wipe();
        trainingExp = training(pokemonLevel);
        printf("\n You trained your %s and got %d experience points!", starterPokemon, trainingExp);
        pokemonExp += trainingExp;
        getch();
    } else if (action == 3) {
        gymBattle();
    }
    wipe();
}

void venture() {
    wipe();
    int venturing = rand() % 5 + 1; // randomly choose between 1 to 5 for the ventures
    int freeExp, freeMoney;

    freeMoney = rand() % 91 + 10; // randomly choose between 10 to 100
    freeExp = training(pokemonLevel);

    if (venturing == 1) {
        printf("You and your %s strolled into Hogwarts Academy and was given %d experience points by a random wizard!\n", starterPokemon, freeExp);
        pokemonExp += freeExp;
        getch();
    } else if (venturing == 2) {
        printf("\n /(oo)\\ Ooooops, you stepped on a banana, slipped, and got reincarnated into another universe.\n Somehow you got %d experience points!", freeExp);
        pokemonExp += freeExp;
        getch();
    } else if (venturing == 3) {
        printf("\n Your %s sniffed something sweet on a tree! It seems to be Maybelle's Candy.\n", starterPokemon);
        candy++;
        getch();
    } else if (venturing == 4) {
        printf("\n Your %s was running around when it found a Red X on a ground somewhere. You dug it up and got $%d money!", starterPokemon, freeMoney);
        money += freeMoney;
        getch();
    } else if (venturing == 5) {
        freeMoney *= 2;
        money += freeMoney;
        candy++;
        printf("\n You chanced upon a waterfall with a secret base! You looked it up and found a treasure chest with: \n $%d money\n 1 Candy", freeMoney);
        getch();
    }
    wipe();
}

int training(int level) {
    int cap = levelingFormula(level);
    int minGain = (cap * 5) / 100; // 5% of exp cap
    int maxGain = (cap * 10) / 100; // 10% of exp cap
    return rand() % (maxGain - minGain + 1) + minGain; // Randomly grant the player 5-10% of exp cap
}

void gymBattle() { // opponents to choose from
    wipe();
    int opponentChoice;
    printf("\n(--) [1] Crissa - Magikarp  LV 1    (--)\n");
    printf("\n(^^) [2] Sheba -  Rapidash  LV 10   (^^)\n");
    printf("\n(++) [3] Rival -  Mewtwo    LV 100  (++)\n\n");
    printf("Choose opponent: ");
    if (scanf("%d", &opponentChoice) != 1) {
        while(getchar() != '\n');
        wipe();
        return;
    }

    switch (opponentChoice) {
        case 1:
            battleCrissa();
            break;
        case 2:
            battleSheba();
            break;
        case 3:
            battleRival();
            break;
        default:
            puts("Invalid opponent.");
            getch();
            break;
    }
    wipe();
}

void battleCrissa() { // she's basically a punching bag and free rewards lol
    int magikarpHP = 100, winExp, winMoney;

    if (pokemonHP == 0) {
        printf("It looks like your %s needs some rest before it can battle again!", starterPokemon);
        // if pokemonHP is 0 it will not proceed with any battles.
        return;
    }

    wipe();
    printf("\n Crissa: Hmph. You dare to belittle me? I won't let that slide.\n");
    getch();
    printf("\n Crissa: Magikarp let's bully them!\n");
    magikarp = 1;
    getch();
    printf("\n %s: %s let's beat her Magikarp!", name, starterPokemon);
    getch();

    while(1) {
        wipe();
        printf("\n Magikarp       > ");
        displayHP(magikarpHP, 100);

        printf("\n %-15s> ", starterPokemon);
        displayHP(pokemonHP, pokemonMaxHP);
        printf("\n");
        showMoves();
        printf("\n Choose a move: ");

        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
            clearBuffer();
            continue;
        }

        printf("\n Magikarp used Splash! It does nothing\n");
        printf("\n %s used %s and it dealt %d damage!", starterPokemon, moveset[choice - 1], movePower[choice - 1]);
        magikarpHP -= movePower[choice - 1];
        getch();

        if (magikarpHP <= 0) { // winning against Crissa give the player 10-20% of exp cap.
            wipe();
            winExp = training(pokemonLevel) * 2;
            winMoney = rand() % 50 + 1; // grant 1 to 50 money
            printf("\n Magikarp has fainted!\n");
            pokemonExp += winExp;
            money += winMoney;
            printf("\n You defeated Crissa and gained %d exp and $%d money\n", winExp, winMoney);
            printf("\n Crissa: HMPH! (**) (**) ");
            return;
        }
    }
}

void battleSheba() {
    int rapidashHP = 250, rapidashAttack, winExp, winMoney, flag = 0;
    int rapidashDMG[] = {70, 65, 90, 80};
    char *rapidashMove[] = {"Poison Kick", "Stomp", "Flame Tail", "Hoof Smash"};

    if (pokemonHP == 0) {
        printf("It looks like your %s needs some rest before it can battle again!", starterPokemon);
        return;
    }

    wipe();
    printf("\n Sheba: So you've chosen death.\n");
    getch();
    printf("\n Sheba: Rapidash let's show them who's boss!\n");
    rapidash = 1;
    getch();
    printf("\n %s: %s let's get em!", name, starterPokemon);
    getch();

    while (1) {
        wipe();
        rapidashAttack = rand() % 4; // generate a random number between 0 to 3, which will be used for the attack
        printf("\n Rapidash       > ");
        displayHP(rapidashHP, 250);

        printf("\n %-15s> ", starterPokemon);
        displayHP(pokemonHP, pokemonMaxHP);
        printf("\n");
        showMoves();
        printf("\n Choose a move: ");

        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
            clearBuffer();
            continue;
        }

        printf("\n Rapidash used %s and it dealt %d damage!\n", rapidashMove[rapidashAttack], rapidashDMG[rapidashAttack]);
        pokemonHP -= rapidashDMG[rapidashAttack];
        getch();

        if (pokemonHP <= 0) {
            wipe();
            pokemonHP = 0;
            flag = 1; // to ensure that the opponent will win if it got the player's Pokemon's hp to 0 first
            // i doubt it will happen though, but just in case
            printf("\n Your %s fainted", starterPokemon);
            return;
        }

        printf("\n %s used %s and it dealt %d damage!", starterPokemon, moveset[choice - 1], movePower[choice - 1]);
        rapidashHP -= movePower[choice - 1];
        getch();

        if (rapidashHP <= 0 && flag == 0) {
            wipe();
            winExp = training(pokemonLevel) * 5; // 25-50% of exp cap
            winMoney = rand() % 151 + 50; // 50-150 money
            printf("\n Rapidash fainted!\n");
            pokemonExp += winExp;
            money += winMoney;
            printf("\n You defeated Sheba and gained %d exp and %d money.\n", winExp, winMoney);
            printf("\n Sheba: Aww man.");
            return;
        }
    }
}

void battleRival() {
    int mewtwoHP = 550, mewtwoAttack, winExp, winMoney, flag = 0;
    int mewtwoDMG[] = {100, 90, 95, 110};
    char *mewtwoMove[] = {"Psystrike", "Thunderbolt", "Foul Play", "Fire Blast"};

    if (pokemonHP == 0) {
        printf("It looks like your %s needs some rest before it can battle again!", starterPokemon);
        return;
    }

    wipe();
    printf("\n Rival: ...\n");
    getch();
    printf("\n Rival sent out Mewtwo!\n");
    mewtwo = 1;
    getch();
    printf("\n %s: %s I choose you!", name, starterPokemon);
    getch();

    while (1) {
        wipe();
        mewtwoAttack = rand() % 4; // generate a random number between 0 to 3, which will be used for the attack
        printf("\n Mewtwo         > ");
        displayHP(mewtwoHP, 550);

        printf("\n %-15s> ", starterPokemon);
        displayHP(pokemonHP, pokemonMaxHP);
        printf("\n");
        showMoves();
        printf("\n Choose a move: ");

        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
            clearBuffer();
            continue;
        }

        printf("\n Mewtwo used %s and it dealt %d damage!\n", mewtwoMove[mewtwoAttack], mewtwoDMG[mewtwoAttack]);
        pokemonHP -= mewtwoDMG[mewtwoAttack];
        getch();

        if (pokemonHP <= 0) {
            wipe();
            pokemonHP = 0;
            flag = 1;
            printf("\n Your %s fainted", starterPokemon);
            return;
        }

        printf("\n %s used %s and it dealt %d damage!", starterPokemon, moveset[choice - 1], movePower[choice - 1]);
        mewtwoHP -= movePower[choice - 1];
        getch();

        if (mewtwoHP <= 0 && flag == 0) {
            wipe();
            printf("\n \(**)/ Congratulations! You finally defeated the Rival!");
            charmander = 1, charmeleon = 1, charizard = 1, bulbasaur = 1, ivysaur = 1, venusaur = 1, squirtle = 1, wartortle = 1, blastoise = 1, pikachu = 1, magikarp = 1, rapidash = 1, mewtwo = 1;
            theEnd = 1;
            return;
        }
    }
}

void pokedex() { // some pokemon entries
    wipe();
    printf("========================================================================================================================\n");
    if (bulbasaur > 0) {
        printf("\n>> Bulbasaur #0001 >>\n");
        printf("\n~~~ For some time after its birth, it uses the nutrients that are packed into the seed on its back in order to grow. ~~~\n");
        printf("\n(**) Height: 2' 04\"      (**)\n(**) Weight: 15.2 lbs    (**)\n(**) Category: Seed      (**)\n(**) Abilities: Overgrow (**)\n");
        }
    if (ivysaur > 0) {
        printf("\n>> Ivysaur #0002 >>\n");
        printf("\n~~~ The more sunlight Ivysaur bathes in, the more strength wells up within it, allowing the bud on its back to grow larger. ~~~\n");
        printf("\n(**) Height: 3' 03\"      (**)\n(**) Weight: 28.7 lbs    (**)\n(**) Category: Seed      (**)\n(**) Abilities: Overgrow (**)\n");
    }
    if (venusaur > 0) {
        printf("\n>> Venusaur #0003 >>\n");
        printf("\n~~~ While it basks in the sun, it can convert the light into energy. As a result, it is more powerful in the summertime. ~~~\n");
        printf("\n(**) Height: 6' 07\"      (**)\n(**) Weight: 220.5 lbs   (**)\n(**) Category: Seed      (**)\n(**) Abilities: Overgrow (**)\n");
    }
    if (charmander > 0) {
        printf("\n>> Charmander #0004 >>\n");
        printf("\n~~~ The flame on its tail shows the strength of its life-force. If Charmander is weak, the flame also burns weakly. ~~~\n");
        printf("\n(**) Height: 2' 00\"     (**)\n(**) Weight: 18.7 lbs   (**)\n(**) Category: Lizard   (**)\n(**) Abilities: Blaze   (**)\n");
    }
    if (charmeleon > 0) {
        printf("\n>> Charmeleon #0005 >>\n");
        printf("\n~~~ When it swings its burning tail, the temperature around it rises higher and higher, tormenting its opponents. ~~~\n");
        printf("\n(**) Height: 3' 07\"     (**)\n(**) Weight: 41.9 lbs   (**)\n(**) Category: Flame    (**)\n(**) Abilities: Blaze   (**)\n");
    }
    if (charizard > 0) {
        printf("\n>> Charizard #0006 >>\n");
        printf("\n~~~ If Charizard becomes truly angered, the flame at the tip of its tail burns in a light blue shade. ~~~\n");
        printf("\n(**) Height: 5' 07\"     (**)\n(**) Weight: 199.5 lbs  (**)\n(**) Category: Flame    (**)\n(**) Abilities: Blaze   (**)\n");
    }
    if (squirtle > 0){
        printf("\n>> Squirtle #0007 >>\n");
        printf("\n~~~ After birth, its back swells and hardens into a shell. It sprays a potent foam from its mouth. ~~~\n");
        printf("\n(**) Height: 1' 08\"      (**)\n|| Weight: 19.8 lbs      (**)\n|| Category: Tiny Turtle (**)\n|| Abilities: Torrent    (**)\n");
    }
    if (wartortle > 0) {
        printf("\n>> Wartortle #0008 >>\n");
        printf("\n~~~ Wartortle’s long, furry tail is a symbol of longevity, so this Pokémon is quite popular among older people. ~~~\n");
        printf("\n(**) Height: 3' 03\"      (**)\n(**) Weight: 49.6 lbs    (**)\n(**) Category: Turtle    (**)\n(**) Abilities: Torrent  (**)\n");
    }
    if (blastoise > 0) {
        printf("\n>> Blastoise #0009 >>\n");
        printf("\n~~~ It deliberately increases its body weight so it can withstand the recoil of the water jets it fires. ~~~\n");
        printf("\n(**) Height: 5' 03\"       (**)\n(**) Weight: 188.5 lbs    (**)\n(**) Category: Shellfish  (**)\n|| Abilities: Torrent     (**)\n");
    }
    if (pikachu > 0) {
        printf("\n>> Pikachu #0025 >>\n");
        printf("\n~~~ When it is angered, it immediately discharges the energy stored in the pouches in its cheeks. ~~~\n");
        printf("\n(**) Height: 1' 04\"    (**)\n(**) Weight: 13.2 lbs  (**)\n(**) Category: Mouse   (**)\n(**) Abilities: Static (**)\n");
    }
    if (magikarp > 0) {
        printf("\n>> Magikarp #0129 >>\n");
        printf("\n~~~ An underpowered, pathetic Pokémon. It may jump high on rare occasions but never more than seven feet. ~~~\n");
        printf("\n(**) Height: 2' 11\"        (**)\n(**) Weight: 22.0 lbs      (**)\n(**) Category: Fish        (**)\n(**) Abilities: Swift Swim (**)\n");
    }
    if (rapidash > 0) {
        printf("\n>> Rapidash #0078 >>\n");
        printf("\n~~~ It gallops at nearly 150 mph. With its mane blazing ferociously, it races as if it were an arrow. ~~~\n");
        printf("\n(**) Height: 5' 07\"                    (**)\n(**) Weight: 209.4 lbs                 (**)\n(**) Category: Fire Horse              (**)\n(**) Abilities: Ran Away & Flash Fire  (**)\n");
    }
    printf("\n========================================================================================================================\n");
    printf("\n\nPress any key to go back.\n");
    getch();
    wipe();
}

void pokeMart() {
    wipe();
    int product, quantity, shopChoice, cost;
    char shopConfirm;

    while (1) {
        printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
        printf("* Pika! Welcome to Lyca's PokeMart! Searching for something legendary or just a browse? *\n\n");
        printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
        printf(">>>>>>----------------------------|>>>\n\n");
        printf(" Lyca: Please browse our products!\n\n");
        printf(">>>>>>----------------------------|>>>\n\n");
        printf("________________________________________________________\n\n");
        printf(" [1] Maybelle's Candy - $100 - Level Up your Pokemon\n");
        printf(" [2] Pokemon-Inspired Outfits\n");
        printf(" [0] Exit\n");
        printf("________________________________________________________\n\n");
        printf("Lyca: Which product do you want? ");
        if (scanf("%d", &product) != 1) {
            wipe();
            while(getchar() != '\n');
            continue;
        }

        switch (product) {
            case 1:  // Maybelle's Candy
                printf("Lyca: How many candies do you want? ");
                if (scanf("%d", &quantity) != 1) {
                    while(getchar() != '\n');
                    break;
                }
                cost = quantity * 100;
                if (quantity > 0 && money >= cost) {
                    printf("Lyca: You bought %d Maybelle's Candy! I'm sure your %s will love it!\n", quantity, starterPokemon);
                    money -= cost;
                    candy += quantity;
                    getch();
                } else if (quantity <= 0) {
                    printf("Lyca: Invalid quantity. Please enter a positive number\n");
                    getch();
                } else {
                    printf("Lyca: You don't have enough money lmao.\n");
                    getch();
                }
                break;
            case 2:
                wipe();
                printf("Lyca: Here's our pokemon-inspired outfits!\n");
                printf("\n\n");
                printf("'''''''''''''''''''''''''''''''''''''\n");
                printf("\n [1] Kigurumi (Onesies)\n");
                printf("\n [2] Gijinka (Humanized Pokemon)\n");
                printf("\n [3] Eevee Evolutions\n\n");
                printf("'''''''''''''''''''''''''''''''''''''\n\n");
                printf("Lyca: Which outfit do you want? ");
                if (scanf("%d", &shopChoice) != 1) {
                    printf("Invalid input.\n");
                    getch();
                    while(getchar() != '\n');
                    break;
                }

                switch (shopChoice) {
                    case 1:
                        printf("[Y/N] Are you ready to gear up with the Kigurumi (Onesies) outfit? ");
                        scanf(" %c", &shopConfirm);
                        clearBuffer();
                        if (shopConfirm == 'Y' || shopConfirm == 'y') {
                            printf("Lyca: You bought the Kigurumi (Onesies) outfit successfully!\n");
                            outfit1 = 1;
                        } else {
                            printf("Lyca: Oh ok then.\n");
                        }
                        break;
                    case 2:
                        printf("[Y/N] Would you like to channel your inner Pokemon with this outfit? ");
                        scanf(" %c", &shopConfirm);
                        clearBuffer();
                        if (shopConfirm == 'Y' || shopConfirm == 'y') {
                            printf("Lyca: You bought the Gijinka (Humanized Pokemon) outfit successfully!\n");
                            outfit2 = 1;
                        } else {
                            printf("Lyca: Oh ok then.\n");
                        }
                        break;
                    case 3:
                        printf("[Y/N] Are the Eevee Evolutions the perfect choice for your adventure? ");
                        scanf(" %c", &shopConfirm);
                        clearBuffer();
                        if (shopConfirm == 'Y' || shopConfirm == 'y') {
                            printf("Lyca: You bought the Eevee Evolutions outfit successfully!\n");
                            outfit3 = 1;
                        } else {
                            printf("Lyca: Oh ok then.\n");
                        }
                        break;
                    default:
                        printf("Lyca: Unfortunately, that's not part of our selection.\n");
                        getch();
                }
                break;
            case 0:
                printf("Thank you for visiting the PokeMart! See you next time!\n");
                getch();
                wipe();
                return;
            default:
                printf("Invalid product choice. Please select a valid option.\n");
        }
        wipe();
    }
    wipe();
}

void profile() {
    int itemSelect;
    wipe();
    printf("       ~~~~~~~~~~~~~\n\n");
    puts("       *  PROFILE  *\n");
    printf("       ~~~~~~~~~~~~~\n\n");
    printf("<======================================>\n");
    printf("  Trainer Name: %s\n", name);
    printf("  Outfit: %s\n", outfit);
    printf("  Money: $%d\n", money);
    printf("<======================================>\n\n");
    printf("  %s\n  Level: %d [%d/%d]\n  Health: %d/%d\n\n", starterPokemon, pokemonLevel, pokemonExp, levelingFormula(pokemonLevel), pokemonHP, pokemonMaxHP);
    printf("         <> Moves <>\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    showMoves();
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("\n         <> Bag <>\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");

    if (candy > 0) {
        printf("[1] Maybelle's Candy: %d\n", candy);
    }
    if (outfit1) {
        printf("[2] Kigurumi (Onesies)\n");
    }
    if (outfit2) {
        printf("[3] Gijinka (Human-sized Pokemon)\n");
    }
    if (outfit3) {
        printf("[4] Eeveelution Outfit (Jolteon)\n");
    }

    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("\n[0 - exit] Select item: ");
    if (scanf("%d", &itemSelect) != 1) {
        while(getchar() != '\n');
        printf("Invalid item.\n");
        getch();
        wipe();
        return;
    }

    if (itemSelect == 0) {
        wipe();
        return;
    } else if (itemSelect == 1 && candy > 0) {
        printf("[y/n] Confirm use candy? ");
        if (scanf(" %c", &confirm) != 1) {
            printf("Invalid confirmation.\n");
            while(getchar() != '\n');
            getch();
            wipe();
            return;
        }

        if (confirm == 'Y' || confirm == 'y') {
            printf("Your %s gobbled the candy in one bite!", starterPokemon);
            pokemonLevel += 1;
            pokemonMaxHP += 20;
            pokemonHP = pokemonMaxHP;
            candy -= 1;
            getch();
            wipe();
            return;
        }
    } else if (itemSelect == 2 && outfit1) {
        snprintf(outfit, sizeof(outfit), "Kigurumi Onesies");
    } else if (itemSelect == 3 && outfit2) {
        snprintf(outfit, sizeof(outfit), "Gijinka");
    } else if (itemSelect == 4 && outfit3) {
        snprintf(outfit, sizeof(outfit), "Jolteon Outfit");
    } else {
        printf("Item nonexistent.");
    }
    wipe();
}

void pokeCenter() {
    char healConfirm;
    wipe();
    printf("[][][][][] Poke Center [][][][][]\n\n");
    printf("\n Nurse Maybelle: Hello %s. Are you here to heal your %s?[y/n]: ", name, starterPokemon);

    if (scanf(" %c", &healConfirm) != 1) {
            while(getchar() != '\n');
    }

    if (healConfirm == 'Y' || healConfirm == 'y') {
        printf("\n Nurse Maybelle: All done. Your %s is now back to shape and is ready for the next challenge!\n", starterPokemon);
        pokemonHP = pokemonMaxHP;
        getch();
    } else if (healConfirm == 'N' || healConfirm == 'n') {
        printf("\n Nurse Maybelle: Oh alright then. See you next time!\n");
        getch();
    }
    wipe();
}

int levelingFormula(int n) {
    if (pokemonLevel > 5) {
        return (int)(4 * pow(n, 3)) / 10;
    } else {
        return 100;
    }
}

void showMoves() {
    for (int i = 0; i < 4; i++) {
        printf("\n >> %d. %-15s \t Power: %3d << \n", i + 1, moveset[i], movePower[i]);
    } // the %-15s and %3d are for space formatting
}

void displayHP(int currentHP, int maxHP) {
    int barLength = 20;
    int filled = (currentHP * barLength) / maxHP;

    printf("%3d/%3d [", currentHP, maxHP);
    for (int i = 0; i < filled; i++) {
            printf("+");
    }
    for (int i = filled; i < barLength; i++) {
            printf("-");
    }
    printf("]");
}
