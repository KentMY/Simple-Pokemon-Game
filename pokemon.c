#include <stdio.h>
#include <math.h> // for pow() and the formula for leveling
#include <stdlib.h> // for rand() and some things
#include <string.h> // for string manipulations
#include <unistd.h> // for sleep()
#include <time.h> // for random numbers to be randomize more than once.
#include <conio.h> // if getch() doesn't work include this

/*/
 * Simple Pokemon Game
 * This game only lets the player use 1 pokemon for the entirety of the game. So,
 * consider it a challenge. lol.
/*/

// Global variables:

const int pokemonMaxHP = 100;
int candy = 20;
int money = 0, choice, action;
int pokemonLevel = 1, pokemonExp = 0, pokemonHP, evolved = 0, evolvedAgain = 0;
int charmander = 0, charmeleon = 0, charizard = 0, bulbasaur = 0, ivysaur = 0, venusaur = 0, squirtle = 0, wartortle = 0, blastoise = 0, pikachu = 0, magikarp = 0, treecko = 0, rapidash = 0, arbok = 0, pidgey = 0, nidoran = 0; // for pokedex
char starterPokemon[20];
char name[11];
char confirm;
char *moveset[] = {"Tackle", "Scratch", "Spit", "Dirt Throw"};



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
void battleLyca();
void battleSheba();
void battleKent();
void battleRival();
void pokedex();
void pokeMart();
void profile();
int levelingFormula(int N);
void showMoves();

int main() {
    srand(time(NULL)); // to seed(not the sus one) em random numbers

    printf("Enter name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // exception handling to consume newline

    printf("Hello %s. Your adventure will start now\n", name);
    getch();
    wipe();
    puts("Prof. Oak: Welcome to the World of Pokemon!");
    getch();
    puts("Prof. Oak: In this perilous world, evil run rampant. But a pokemon will help you tread through safely.");
    getch();
    puts("Prof. Oak: Therefore, I will hand you one of these three that I wish you foster.");
    puts("[1] - Charmander");
    puts("[2] - Bulbasaur");
    puts("[3] - Squirtle");
    printf("Prof. Oak: So which one have you taken a liken to? ");
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
    }

    switch (choice) {
        case 1:
            charmander = 1;
            // below is an assignment of value to the string starterPokemon
            snprintf(starterPokemon, sizeof(starterPokemon), "Charmander");
            puts("Prof. Oak: Oh, a Charmander, is it? A nice pick.");
            break;
        case 2:
            bulbasaur = 1;
            snprintf(starterPokemon, sizeof(starterPokemon), "Bulbasaur");
            puts("Prof. Oak: Bulbasaur? A cute vegetable, not bad.");
            break;
        case 3:
            squirtle = 1;
            snprintf(starterPokemon, sizeof(starterPokemon), "Squirtle");
            puts("Prof. Oak: Squirtle, huh. Very well");
            break;
        default:
            pikachu = 1;
            snprintf(starterPokemon, sizeof(starterPokemon), "Pikachu");
            puts("Prof. Oak: Well, that is not part of the choice, but i'll give you a Pikachu");
            break;
    }
    getch();
    printf("Prof. Oak: Now go forth and venture this world with your companion %s\n", starterPokemon);
    getch();
    wipe();

    do {
        evoAndLevel();

        puts("[1] Adventure");
        puts("[2] Pokedex");
        puts("[3] PokeMart");
        puts("[4] Profile");
        printf("Enter action: ");

        if (scanf("%d", &action) != 1) {
            while(getchar() != '\n');
        }

        switch (action) {
            case 1:
                adventure();
                break;
            case 2:
                pokedex();
                break;
            case 3:
                pokeMart();
                break;
            case 4:
                profile();
                break;
            default:
                puts("Invalid action. Please repeat.");
                wipe();
                break;
        }


    } while (1);


    return 0;
}

void clearBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void wipe() {
    system("cls"); // "clear" if "cls" doesn't work.
}

void evolution() {
    if (pokemonLevel == 16) {
        if (choice == 1) {
            snprintf(starterPokemon, sizeof(starterPokemon), "Charmeleon");
            charmeleon = 1;
        } else if (choice == 2) {
            snprintf(starterPokemon, sizeof(starterPokemon), "Ivysaur");
            ivysaur = 1;
        } else if (choice == 3) {
            snprintf(starterPokemon, sizeof(starterPokemon), "Wartortle");
            wartortle = 1;
        }
    }

    if (pokemonLevel == 32) {
        if (choice == 1) {
            snprintf(starterPokemon, sizeof(starterPokemon), "Charizard");
            charizard = 1;
        } else if (choice == 2) {
            snprintf(starterPokemon, sizeof(starterPokemon), "Venusaur");
            venusaur = 1;
        } else if (choice == 3) {
            snprintf(starterPokemon, sizeof(starterPokemon), "Blastoise");
            blastoise = 1;
        }
    }
}

void evoAndLevel() {
    while (pokemonExp >= levelingFormula(pokemonLevel)) { // Handle evolutions and leveling
        pokemonExp = 0;
        pokemonLevel++;
        printf("Your %s leveled up!\n", starterPokemon);
        }

        if (pokemonLevel == 16 && evolved == 0) {
            printf("Hold on\n");
            sleep(2);
            printf("Something is happening to your %s, it seems to be glowing in such resplendent light!\n", starterPokemon);
            sleep(3);
            printf("Oh what's this? It's actually evolving!\n");
            sleep(3);
            printf("Your %s evolved into ", starterPokemon);
            evolution();
            printf("%s!\n", starterPokemon);
            evolved = 1;
            getch();
            wipe();
        } else if (pokemonLevel == 32 && evolvedAgain == 0) {
            printf("Oh damn your %s is glowing again!\n", starterPokemon);
            sleep(2);
            printf("Color me surprise! This glow is even brighter than its previous evolution, is this perhaps its final evolution?\n");
            sleep(3);
            printf("*zzziing* Your %s evolved into ", starterPokemon);
            evolution();
            printf("%s!\n", starterPokemon);
            evolvedAgain = 1;
            getch();
            wipe();
        }
}

void adventure() {
    wipe();
    int opponentChoice, trainingExp;

    printf("[1] Embark on a journey with your %s and take a step into the world of adventure.\n", starterPokemon);
    printf("[2] Train your %s\n", starterPokemon);
    printf("[3] Gym Battle\n");
    printf("Enter action: ");
    scanf("%d", &action);

    if (action == 1) {
        venture();

    } else if (action == 2) {
        trainingExp = training(pokemonLevel);
        printf("You trained your %s and got %d", starterPokemon, trainingExp);
        pokemonExp += trainingExp;
        getch();
    } else if (action == 3) {
        printf("Are you ready to take on the Gym now?[y/n]: ");

        if (scanf(" %c", &confirm) != 1) {
            printf("Invalid input.\n");
            clearBuffer();
            getch();
            return;
        }
        clearBuffer();

        if (confirm == 'Y' || confirm == 'y') {
            gymBattle();
        } else if (confirm == 'N' || confirm == 'n') {
            printf("Alrighty.\n");
        } else {
            printf("Invalid input, must enter either 'y' or 'n'\n");
        }

    }

    getch();
    wipe();
}

void venture() {
    wipe();
    int venturing = rand() % 5 + 1;
    int freeExp;
    freeExp = training(pokemonLevel);

    if (venturing == 1) {
        printf("You and your %s strolled into Hogwarts Academy and was given %d experience points by a random wizard!\n", starterPokemon, freeExp);
        pokemonExp += freeExp;
    } else if (venturing == 2) {
        printf("You stepped on a banana, slipped, and got reincarnated into another universe. Somehow you got %d experience points!", freeExp);
        pokemonExp += freeExp;
    } else if (venturing == 3) {
        printf("Your %s sniffed something suspicious on a tree! It seems to be a Maybelle's Candy.\n", starterPokemon);
        candy++;
    } else if (venturing == 4) {
        printf("I printed 4\n");
    } else if (venturing == 5) {
        printf("I printed 5\n");
    }

    getch();
    wipe();
}

int training(int level) {
    int cap = levelingFormula(level);
    int minGain = (cap * 5) / 100;
    int maxGain = (cap * 10) / 100;
    return rand() % (maxGain - minGain + 1) + minGain;
}

void gymBattle() {
    wipe();
    int opponentChoice;
    printf("[1] Crissa - Magikarp LV 1\n");
    printf("[2] Lyca - Treecko LV 5\n");
    printf("[3] Sheba - Rapidash LV 10\n");
    printf("[4] Kent - Arbok LV 15\n");
    printf("[5] Rival -  Mewtwo LV 100\n");
    printf("Choose opponent: ");
    scanf("%d", &opponentChoice);

    switch (opponentChoice) {
        case 1:
            //battleCrissa();
            break;
        case 2:
            //battleLyca();
            break;
        case 3:
            //battleSheba();
            break;
        case 4:
            //battleKent();
            break;
        case 5:
            //battleMaybelle();
            break;
        default:
            puts("Invalid opponent.");
            break;
    }

    getch();
    wipe();
}

void battleCrissa() {

}

void battleLyca() {

}

void battleSheba() {

}

void battleKent() {

}

void battleRival() {

}

void pokedex() {
    wipe();
    if (bulbasaur > 0) {
        printf("\n|| Bulbasaur #0001\n");
        printf("|| For some time after its birth, it uses the nutrients that are packed into the seed on its back in order to grow.\n");
        printf("|| Height: 2' 04\" \n|| Weight: 15.2 lbs\n|| Category: Seed\n|| Abilities: Overgrow\n");
        }
    if (ivysaur > 0) {
        printf("\n|| Ivysaur #0002\n");
        printf("|| The more sunlight Ivysaur bathes in, the more strength wells up within it, allowing the bud on its back to grow larger.\n");
        printf("|| Height: 3' 03\" \n|| Weight: 28.7 lbs\n|| Category: Seed\n|| Abilities: Overgrow\n");
    }
    if (venusaur > 0) {
        printf("\n|| Venusaur #0003\n");
        printf("|| While it basks in the sun, it can convert the light into energy. As a result, it is more powerful in the summertime.\n");
        printf("|| Height: 6' 07\" \n|| Weight: 220.5 lbs\n|| Category: Seed\n|| Abilities: Overgrow\n");
    }
    if (charmander > 0) {
        printf("\n|| Charmander #0004\n");
        printf("|| The flame on its tail shows the strength of its life-force. If Charmander is weak, the flame also burns weakly.\n");
        printf("|| Height: 2' 00\" \n|| Weight: 18.7 lbs\n|| Category: Lizard\n|| Abilities: Blaze\n");
    }
    if (charmeleon > 0) {
        printf("\n|| Charmeleon #0005\n");
        printf("|| When it swings its burning tail, the temperature around it rises higher and higher, tormenting its opponents.\n");
        printf("|| Height: 3' 07\" \n|| Weight: 41.9 lbs\n|| Category: Flame\n|| Abilities: Blaze\n");
    }
    if (charizard > 0) {
        printf("\n|| Charizard #0006\n");
        printf("|| If Charizard becomes truly angered, the flame at the tip of its tail burns in a light blue shade.\n");
        printf("|| Height: 5' 07\" \n|| Weight: 199.5 lbs\n|| Category: Flame\n|| Abilities: Blaze\n");
    }
    if (squirtle > 0){
        printf("\n|| Squirtle #0007\n");
        printf("|| After birth, its back swells and hardens into a shell. It sprays a potent foam from its mouth.\n");
        printf("|| Height: 1' 08\" \n|| Weight: 19.8 lbs\n|| Category: Tiny Turtle\n|| Abilities: Torrent\n");
    }
    if (wartortle > 0) {
        printf("\n|| Wartortle #0008\n");
        printf("|| Wartortle’s long, furry tail is a symbol of longevity, so this Pokémon is quite popular among older people.\n");
        printf("|| Height: 3' 03\" \n|| Weight: 49.6 lbs\n|| Category: Turtle \n|| Abilities: Torrent\n");
    }
    if (blastoise > 0) {
        printf("\n|| Blastoise #0009\n");
        printf("|| It deliberately increases its body weight so it can withstand the recoil of the water jets it fires.\n");
        printf("|| Height: 5' 03\" \n|| Weight: 188.5 lbs\n|| Category: Shellfish \n|| Abilities: Torrent\n");
    }
    if (magikarp > 0) {
        printf("\n|| Magikarp #0129\n");
        printf("|| An underpowered, pathetic Pokémon. It may jump high on rare occasions but never more than seven feet.\n");
        printf("|| Height: 2' 11\" \n|| Weight: 22.0 lbs\n|| Category: Fish\n|| Abilities: Swift Swim\n");
        }
    if (treecko > 0) {
        printf("\n|| Treecko #0252\n");
        printf("|| The small hooks on the soles of its feet latch on to walls and ceilings, so it will never fall even while hanging upside down.\n");
        printf("|| Height: 1' 08\" \n|| Weight: 11.0 lbs\n|| Category: Wood Gecko\n|| Abilities: Overgrow\n");
        }
    if (rapidash > 0) {
        printf("\n|| Rapidash #0078\n");
        printf("|| It gallops at nearly 150 mph. With its mane blazing ferociously, it races as if it were an arrow.\n");
        printf("|| Height: 5' 07\" \n|| Weight: 209.4 lbs\n|| Category: Fire Horse\n|| Abilities: Ran Away\n Flash Fire\n");
        }
    if (arbok > 0) {
        printf("\n|| Arbok #0024\n");
        printf("|| The pattern on its belly appears to be a frightening face. Weak foes will flee just at the sight of the pattern.\n");
        printf("|| Height: 11' 06\" \n|| Weight: 143.3 lbs\n|| Category: Wood Gecko\n|| Abilities: Overgrow\n");
    }
    if (pidgey > 0){
           printf("\n|| Pidgey #0016\n");
        printf("|| Very docile. If attacked, it will often kick up sand to protect itself rather than fight back.\n");
        printf("|| Height: 1' 00\" \n|| Weight: 4'0 lbs\n|| Category: Tiny Bird\n|| Abilities: Keen eye & Tangled eye\n");
    }
    if (nidoran > 0){
        printf("\n|| Nidoran #0032\n");
        printf("|| The horn on a male Nidoran’s forehead contains a powerful poison. This is a very cautious Pokémon, always straining its large ears. Versions: \n");
        printf("|| Height:  1'08\" \n|| Weight: 19.8 lbs\n|| Category: Poison Pin\n|| Abilities:  Poison Point and Rivalry");
    }
    printf("Press any key to continue.\n");
    getch();
    wipe();
}

void pokeMart() {
    wipe();
    int product, quantity, choice, cost;
    char confirm;

    while (1) {  // Loop for repeated purchases until the user exits
        printf("Pika! Welcome to the PokeMart!\n");
        printf("|| \tOur Products:\n");
        printf("[1] Maybelle's Candy - $100 - Level Up your Pokemon\n");
        printf("[2] Pokemon-Inspired Outfits\n");
        printf("[3] Exit\n");
        printf("\nWhich product do you want? ");
        if (scanf("%d", &product) != 1) {  // Validate input
            printf("Invalid input, please try again.\n");
            getch();
            wipe();
            while(getchar() != '\n');  // Clear input buffer
            continue;
        }

        switch (product) {
            case 1:  // Candy
                printf("How many candies do you want? ");
                if (scanf("%d", &quantity) != 1) {
                    printf("Invalid quantity.\n");
                    while(getchar() != '\n');
                    break;
                }
                cost = quantity * 100;
                if (quantity > 0 && money >= cost) {
                    printf("You bought %d Maybelle's Candy! Your %s will love it!\n", quantity, starterPokemon);
                    money -= cost;
                    candy += quantity;
                } else if (quantity <= 0) {
                    printf("Invalid quantity. Enter positive\n");
                    getch();
                } else {
                    printf("You don't have enough money lmao.\n");
                    getch();
                }
                break;

            case 2:  // Outfit
                printf("Available Outfits:\n");
                printf("[1] Kigurumi (Onesies)\n");
                printf("[2] Gijinka (Humanized Pokemon)\n");
                printf("[3] Eevee Evolutions\n");
                printf("Which outfit do you want? ");
                if (scanf("%d", &choice) != 1) {
                    printf("Invalid input.\n");
                    while(getchar() != '\n');
                    break;
                }

                switch (choice) {
                    case 1:
                        printf("[Y/N] Are you ready to gear up with the Kigurumi (Onesies) outfit? ");
                        scanf(" %c", &confirm);
                        if (confirm == 'Y' || confirm == 'y') {
                            printf("You bought the Kigurumi (Onesies) outfit successfully!\n");
                        } else {
                            printf("Purchase cancelled.\n");
                        }
                        break;

                    case 2:
                        printf("[Y/N] Would you like to channel your inner Pokemon with this outfit? ");
                        scanf(" %c", &confirm);
                        if (confirm == 'Y' || confirm == 'y') {
                            printf("You bought the Gijinka (Humanized Pokemon) outfit successfully!\n");
                        } else {
                            printf("Purchase cancelled.\n");
                        }
                        break;

                    case 3:
                        printf("[Y/N] Are the Eevee Evolutions the perfect choice for your adventure? ");
                        scanf(" %c", &confirm);
                        if (confirm == 'Y' || confirm == 'y') {
                            printf("You bought the Eevee Evolutions outfit successfully!\n");
                        } else {
                            printf("Purchase cancelled.\n");
                        }
                        break;

                    default:
                        printf("Invalid Pokemon Outfit.\n");
                }
                break;

            case 3:  // Exit
                printf("Thank you for visiting the PokeMart! See you next time!\n");
                getch();
                wipe();
                return;

            default:
                printf("Invalid product choice. Please select a valid option.\n");
        }

        wipe();  // Reset the interface for the next user interaction
    }
        wipe();  // Reset the interface for the next user interaction
}

void profile() {
    int itemSelect;
    wipe();
    puts("----Profile----");
    printf("Trainer Name: %s\n", name);
    printf("Money: $%d\n\n", money);

    printf("%s  --  Level: %d [%d/%d]  --  MaxHP: %d\n", starterPokemon, pokemonLevel, pokemonExp, levelingFormula(pokemonLevel), pokemonMaxHP);
    printf("Moves:\n");
    showMoves();

    printf("\nBag: \n");

    if (candy > 0) {
        printf("[1] Candy: %d", candy);
    }

    printf("\n[0 - exit] Select item: ");
    if (scanf("%d", &itemSelect) != 1) {
        while(getchar() != '\n');
        printf("Invalid item.\n");
        getch();
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
            candy -= 1;
        }
    } else {
        printf("You don't have such an item. Buy it lol.");
    }

    getch();
    wipe();
}

int levelingFormula(int n) {
    if (pokemonLevel > 5) {
        return (int)(4 * pow(n, 3)) / 5;
    } else {
        return 100;
    }
}

void showMoves() {
    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, moveset[i]);
    }
}
