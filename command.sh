gdbus call -e -o / -d com.system.sharing -m com.system.sharing.RegisterService "com.system.mp4"  "['mp4', 'pdf']"
gdbus call -e -o / -d com.system.sharing -m com.system.sharing.OpenFile "/home/adelaida/Desktop/dbus/example_file/file.mp4"

