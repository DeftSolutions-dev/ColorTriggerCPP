# Color Trigger - C++

[![GitHub](https://img.shields.io/badge/GitHub-DeftSolutions--dev-blue)](https://github.com/DeftSolutions-dev)
[![Telegram](https://img.shields.io/badge/Telegram-devilLucifer69-blue)](https://t.me/devilLucifer69)

ColorTrigger - is a C++ utility program that allows you to trigger actions based on color changes at the cursor's position. It can be useful for automating tasks or interactions in applications or games where color changes signify specific events.

## Usage

1. **Threshold Setting**: When you run the program, it will prompt you to enter a threshold value (from 4 to 20). This threshold represents the maximum allowed difference in color values between two consecutive pixel checks for a change to be detected. Higher values allow for more color variation before triggering an action.

2. **Bind Selection**: After setting the threshold, you'll be prompted to select a bind (X, F, LALT, Mouse3, Mouse4). This bind determines the key or mouse button that, when pressed, triggers the color change detection.

3. **Running the Program**: Once configured, the program will continuously monitor for the specified key or mouse button press. When the trigger key/button is activated, the program will compare the color of the pixel at the cursor's position before and after the key/button press.

4. **Color Change Detection**: If the color difference between the two pixels exceeds the threshold, the program will perform an action (left mouse button click). This can be customized to perform other actions as needed.

5. **Threshold Adjustment**: You can adjust the threshold during runtime using the "Up" and "Down" arrow keys. Increasing the threshold makes color changes less sensitive, while decreasing it makes them more sensitive.

## Example Key Binds

- **X**: Hold down the "X" key to trigger color change detection.
- **F**: Hold down the "F" key to trigger color change detection.
- **LALT**: Hold down the left Alt key (LALT) to trigger color change detection.
- **Mouse3**: Hold down the middle mouse button (Mouse3) to trigger color change detection.
- **Mouse4**: Hold down the fourth mouse button (Mouse4) to trigger color change detection.

## Dependencies

- The program uses the Windows API functions for keyboard and mouse input monitoring.
- It utilizes GDI+ for capturing the pixel color at the cursor's position.

## Disclaimer

This program is intended for educational and experimental purposes. Be aware of the legal and ethical considerations when using automation tools in any software or game. Use responsibly and at your own risk.

## Author

- DesirePro
- Discord: desirepro

Feel free to customize this README with your contact information, usage guidelines, and any additional features or improvements you make to the program.
