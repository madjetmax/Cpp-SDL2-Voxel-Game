import os
import pyperclip

directory = "game"

# g++ -Llib -O3 main.cpp game/*.cpp -lSDL2 -lSDL2_image

clear_inludes: str = ""

dirs_exceptions: list[str] = []

for dir, *_ in os.walk(directory):
    if dir in dirs_exceptions:
        continue

    for fname in os.listdir(dir):
        if fname.endswith('.cpp'):
            clear_inludes += f"{dir.replace("\\", "/")}/*.cpp "
            break

clear_command = f"g++ -Llib -O3 main.cpp {clear_inludes.strip()} -lSDL2 -lSDL2_image"
print(clear_command)
pyperclip.copy(clear_command)