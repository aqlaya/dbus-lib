#!/bin/bash
gdbus call -e -o / -d com.system.sharing -m com.system.sharing.RegisterService "com.system.mp4"  "['mp4', 'pdf']"
gdbus call -e -o / -d com.system.sharing -m com.system.sharing.OpenFile "/home/adelaida/Desktop/dbus/example_file/file.mp4"
gdbus call -e -o / -d com.system.sharing -m com.system.sharing.RegisterService "com.system.handler_pdf" "['pdf', 'fb2', 'ebup']"
gdbus call -e -o / -d com.system.sharing -m com.system.sharing.RegisterService "com.system.handler_videos" "['mp4', 'mov', 'avi', 'wmv', 'flv']"
gdbus call -e -o / -d com.system.sharing -m com.system.sharing.OpenFileUsingService "/home/adelaida/Desktop/dbus/example_file/file.mp4" "com.system.mp4"
gdbus call -e -o / -d com.system.sharing -m com.system.sharing.RegisterService "com.system.handler_photos" "['jpg', 'jpeg']"
gdbus call -e -o / -d com.system.sharing -m com.system.sharing.OpenFileUsingService "/home/adelaida/Desktop/dbus/example_file/file.mp4" "com.fast.fast"
gdbus call -e -o / -d com.system.sharing -m com.system.sharing.OpenFileUsingService "/home/adelaida/Desktop/dbus/example_file/file.pdf" "com.system.mp4"

#example_dbus
gdbus call -e -o / -d com.system.sharing -m com.system.sharing.OpenFile "/home/adelaida/Desktop/Angl.txt" 
gdbus call -e -o / -d com.system.sharing -m com.system.sharing.OpenFileUsingService "/home/adelaida/Desktop/Angl.txt" "com.example.mediaplayer"