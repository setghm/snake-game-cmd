#include "storage.h"
#include <Windows.h>
#include <stdio.h>

#define SETTINGS_FILE   "snake_settings.dat"

static struct StorageSettings_ {
    Language language;
    bool enable_sound;
} StorageSettings;

bool Storage_SaveSettings(bool enable_sound, Language language) {
    // Open the settings file.
    FILE* settings_file = fopen(SETTINGS_FILE, "wb");

    // Check if the file could be opened.
    if (settings_file == NULL) {
        // The file can't be created.
        return false;
    }

    // Update settings.
    StorageSettings.language = language;
    StorageSettings.enable_sound = enable_sound;

    // Write into the file.
    fwrite(&StorageSettings, sizeof(StorageSettings), 1, settings_file);

    // Close the file.
    fclose(settings_file);

    return true;
}

bool Storage_GetSettings(bool* enable_sound, Language* language) {
    FILE* settings_file = fopen(SETTINGS_FILE, "rb");

    // Check if the file can be opened.
    if (settings_file == NULL) {
        MessageBox(0, "The file can't be opened for read", "ERROR", 0);
        return false;
    }

    // Read the file contents.
    fread(&StorageSettings, sizeof(StorageSettings), 1, settings_file);

    // Restore the settings.
    *enable_sound = StorageSettings.enable_sound;
    *language = StorageSettings.language;

    // Close the file.
    fclose(settings_file);

    return true;
}