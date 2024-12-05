#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONFIG_FILE "network_config.txt"
#define MAX_LINE_LENGTH 256

// Function prototypes
void viewConfig();
void updateConfig();
void saveConfig();
void loadConfig();

// Global configuration storage
typedef struct {
    char key[50];
    char value[50];
} Config;

Config configs[10];
int configCount = 0;

int main() {
    int choice;

    loadConfig();

    while (1) {
        printf("\n--- Network Configuration Manager ---\n");
        printf("1. View Configuration\n");
        printf("2. Update Configuration\n");
        printf("3. Save Configuration\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character after input

        switch (choice) {
            case 1:
                viewConfig();
                break;
            case 2:
                updateConfig();
                break;
            case 3:
                saveConfig();
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Load configuration from file
void loadConfig() {
    FILE *file = fopen(CONFIG_FILE, "r");
    if (!file) {
        printf("No existing configuration found. Starting fresh.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    configCount = 0;

    while (fgets(line, sizeof(line), file) && configCount < 10) {
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "\n");

        if (key && value) {
            strncpy(configs[configCount].key, key, sizeof(configs[configCount].key));
            strncpy(configs[configCount].value, value, sizeof(configs[configCount].value));
            configCount++;
        }
    }

    fclose(file);
}

// View current configuration
void viewConfig() {
    if (configCount == 0) {
        printf("No configuration available.\n");
        return;
    }

    printf("\nCurrent Network Configuration:\n");
    for (int i = 0; i < configCount; i++) {
        printf("%s: %s\n", configs[i].key, configs[i].value);
    }
}

// Update configuration
void updateConfig() {
    char key[50], value[50];

    printf("Enter parameter name (e.g., IP, Subnet, Gateway): ");
    fgets(key, sizeof(key), stdin);
    strtok(key, "\n"); // Remove trailing newline

    // Validate specific parameters like Subnet
    if (strcmp(key, "Subnet") == 0) {
        printf("Enter Subnet value (e.g., 255.255.255.0): ");
    } else {
        printf("Enter value: ");
    }

    fgets(value, sizeof(value), stdin);
    strtok(value, "\n"); // Remove trailing newline

    // Check if the key already exists
    for (int i = 0; i < configCount; i++) {
        if (strcmp(configs[i].key, key) == 0) {
            strncpy(configs[i].value, value, sizeof(configs[i].value));
            printf("Configuration updated successfully!\n");
            return;
        }
    }

    // Add new key-value pair
    if (configCount < 10) {
        strncpy(configs[configCount].key, key, sizeof(configs[configCount].key));
        strncpy(configs[configCount].value, value, sizeof(configs[configCount].value));
        configCount++;
        printf("Configuration added successfully!\n");
    } else {
        printf("Configuration limit reached! Cannot add more.\n");
    }
}

// Save configuration to file
void saveConfig() {
    FILE *file = fopen(CONFIG_FILE, "w");
    if (!file) {
        printf("Error saving configuration.\n");
        return;
    }

    for (int i = 0; i < configCount; i++) {
        fprintf(file, "%s=%s\n", configs[i].key, configs[i].value);
    }

    fclose(file);
    printf("Configuration saved successfully!\n");
}