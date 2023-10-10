# Color Trigger - C++

[![GitHub](https://img.shields.io/badge/GitHub-DeftSolutions--dev-blue)](https://github.com/DeftSolutions-dev)
[![Telegram](https://img.shields.io/badge/Telegram-desirepro-blue)](https://t.me/desirepro)

ColorTrigger - is a C++ utility program that allows you to trigger actions based on color changes at the cursor's position. It can be useful for automating tasks or interactions in applications or games where color changes signify specific events.

## Usage

1. **Threshold Setting**: When you run the program, it will prompt you to enter a threshold value (from 4 to 20). This threshold represents the maximum allowed difference in color values between two consecutive pixel checks for a change to be detected. Higher values allow for more color variation before triggering an action.

2. **Milliseconds Setting**: When you start the program, it will prompt you to enter the click milliseconds value (from 1 to 100). This value represents the speed at which the mouse button is pressed when the pixel changes. If you use AWP, SSG in cs go, I recommend from 5 to 8. It all depends on your game and what is convenient for you.

3. **Bind Selection**: After setting the threshold, you'll be prompted to select a bind (X, F, LALT, Mouse4, Mouse5). This bind determines the key or mouse button that, when pressed, triggers the color change detection.
   
4. **Selecting a color source**: If you select the 'cursor', it will check the colors of the pixels around the cursor. If you choose the 'center', it will only check the pixels in the center of the screen, regardless of the screen's resolution or the game's screen resolution. It automatically adjusts to the center. (the center works great for everyone, I recommend it for the game Rainbow Six)

5. **Running the Program**: Once configured, the program will continuously monitor for the specified key or mouse button press. When the trigger key/button is activated, the program will compare the color of the pixel at the cursor's position before and after the key/button press.

6. **Color Change Detection**: If the color difference between the two pixels exceeds the threshold, the program will perform an action (left mouse button click). This can be customized to perform other actions as needed.

7. **Threshold Adjustment**: You can adjust the threshold during runtime using the "Up" and "Down" arrow keys. Increasing the threshold makes color changes less sensitive, while decreasing it makes them more sensitive.

## Example Key Binds

- **X**: Hold down the "X" key to trigger color change detection.
- **F**: Hold down the "F" key to trigger color change detection.
- **LALT**: Hold down the left Alt key (LALT) to trigger color change detection.
- **Mouse4**: Hold down the middle mouse button (Mouse4) to trigger color change detection.
- **Mouse5**: Hold down the fourth mouse button (Mouse5) to trigger color change detection.

## Dependencies

- The program uses the Windows API functions for keyboard and mouse input monitoring and color pixel.

## Disclaimer

This program is intended for educational and experimental purposes. Be aware of the legal and ethical considerations when using automation tools in any software or game. Use responsibly and at your own risk.

## Example of showing work

https://github.com/DeftSolutions-dev/ColorTriggerCPP/assets/59990384/f4ce2564-5b09-4939-bb21-b4c7dc53f177

## Author

- DesirePro
- Discord: desirepro

Feel free to customize this README with your contact information, usage guidelines, and any additional features or improvements you make to the program.
