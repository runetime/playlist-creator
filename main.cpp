#include <iostream>
#include <dirent.h>
#include <fstream>
#include <string.h>

using namespace std;

void getfiles(string dir, string &files, string types) {
    DIR *dp = opendir(dir.c_str());

    struct dirent *entry;

    while ((entry = readdir(dp)) != NULL) {
        string name(entry->d_name);

        if ((name != ".") && (name != "..")) {
            string full = dir + "/" + name;

            // If it's not a directory, append it to the string list.
            // If it is, then dive into that directory.
            if (entry->d_type != DT_DIR) {
                // Check if the extension matches.
                std::string::size_type idx = name.rfind(".");

                // Make sure that an extension was found.
                if (idx != std::string::npos) {
                    std::string extension = name.substr(idx + 1);

                    // Check if the extension is in the types list.
                    if (types.find(extension) != std::string::npos) {
                        files = files + name + "\n";
                    }
                }
            } else {
                getfiles(full, files, types);
            }
        }
    }
}

int main() {
    // How to get a string/sentence with spaces
    string dir = "";
    cout << "Please enter a directory to scan:\n>";
    getline(cin, dir);

    string output = "";
    cout << "Where do you want the resulted playlist file?\n>";
    getline(cin, output);

    string types_default = "flac, mp3, m4a, ogg";
    string types = "";
    cout << "What file extensions to search for (CSV like the default)? (default: flac, mp3, m4a, ogg)";
    getline(cin, types);

    if (strlen(types.c_str()) == 0) {
        types = types_default;
    }

    string files = "";

    // Loop through the directory.
    getfiles(dir, files, types);

    // Let them know what we found.
    cout << files;

    // Write the files to the file they specified.
    std::ofstream out(output);
    out << files;
    out.close();

    return 0;
}
