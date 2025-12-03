#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int jersey;
    char name[50];
    int runs;
    int wickets;
} Player;

// Function prototypes
void addPlayer(Player *players, int *count);
void displayAllPlayers(Player *players, int count);
void updatePlayer(Player *players, int count);
void saveToFile(Player *players, int count);


int main() {
    Player players[100];  
    int count = 0;        
    int choice;

    printf("\n===== CRICKET APPLICATION =====\n");

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Add Player\n");
        printf("2. Display All Players\n");
        printf("3. Update Player Stats\n");
        printf("4. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1:
                addPlayer(players, &count);
                break;
            case 2:
                displayAllPlayers(players, count);
                break;
            case 3:
                updatePlayer(players, count);
                break;
            case 4:
                saveToFile(players, count);
                printf("Data saved. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void addPlayer(Player *players, int *count) {
    if (*count >= 100) {
        printf("Player limit reached!\n");
        return;
    }

    printf("\n--- ADD PLAYER ---\n");
    printf("Enter Jersey Number: ");
    scanf("%d", &players[*count].jersey);
    getchar();

    printf("Enter Player Name: ");
    fgets(players[*count].name, 50, stdin);
    players[*count].name[strcspn(players[*count].name, "\n")] = 0;

    printf("Enter Runs: ");
    scanf("%d", &players[*count].runs);

    printf("Enter Wickets: ");
    scanf("%d", &players[*count].wickets);

    (*count)++;
    printf("Player added successfully!\n");
}

void displayAllPlayers(Player *players, int count) {
    if (count == 0) {
        printf("\nNo players found!\n");
        return;
    }

    printf("\n--- ALL PLAYERS ---\n");
    printf("%-10s %-20s %-10s %-10s\n", "Jersey", "Name", "Runs", "Wickets");
    printf("================================================\n");

    for (int i = 0; i < count; i++) {
        printf("%-10d %-20s %-10d %-10d\n",
               players[i].jersey,
               players[i].name,
               players[i].runs,
               players[i].wickets);
    }
}

void updatePlayer(Player *players, int count) {
    int jersey;
    printf("\n--- UPDATE PLAYER ---\n");
    printf("Enter Jersey Number to update: ");
    scanf("%d", &jersey);
    getchar();

    int matches[100];
    int matchCount = 0;
    for (int i = 0; i < count; i++) {
        if (players[i].jersey == jersey) {
            matches[matchCount] = i;
            matchCount++;
        }
    }

    if (matchCount == 0) {
        printf("Jersey number not found!\n");
        return;
    }

    if (matchCount > 1) {
        printf("\nMultiple players found with this jersey number:\n");
        for (int i = 0; i < matchCount; i++) {
            printf("%d. %s (Runs: %d, Wickets: %d)\n",
                   i + 1,
                   players[matches[i]].name,
                   players[matches[i]].runs,
                   players[matches[i]].wickets);
        }

        printf("Which player do you want to update? (Enter 1-%d): ", matchCount);
        int choice;
        scanf("%d", &choice);

        if (choice < 1 || choice > matchCount) {
            printf("Invalid choice!\n");
            return;
        }

        int playerIndex = matches[choice - 1];
        printf("Updating %s...\n", players[playerIndex].name);

        printf("Enter new Runs: ");
        scanf("%d", &players[playerIndex].runs);

        printf("Enter new Wickets: ");
        scanf("%d", &players[playerIndex].wickets);

        printf("Player updated successfully!\n");
    } else {
        int playerIndex = matches[0];
        printf("Updating %s...\n", players[playerIndex].name);

        printf("Enter new Runs: ");
        scanf("%d", &players[playerIndex].runs);

        printf("Enter new Wickets: ");
        scanf("%d", &players[playerIndex].wickets);

        printf("Player updated successfully!\n");
    }
}

void saveToFile(Player *players, int count) {
    FILE *file = fopen("cricket_data.txt", "w");

    if (file == NULL) {
        printf("Error creating file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %d %d\n",
                players[i].jersey,
                players[i].name,
                players[i].runs,
                players[i].wickets);
    }

    fclose(file);
    printf("Data saved to cricket_data.txt\n");
}
