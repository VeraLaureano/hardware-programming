# **ButtonSequenceLED** 

This Arduino project is a button sequence tracking game, where the user must repeat a sequence of LED lights initially displayed. The LEDs represent a predefined sequence that the user must emulate by pressing the corresponding buttons.

## Operation

The project uses an Arduino Nano along with two buttons and three LEDs: green, yellow, and red. Upon startup, the Arduino displays a sequence of LED lights that the user must remember and replicate by pressing the buttons.

### Game Rules:

1. Each LED represents a specific button:
   - Green LED: Button 1
   - Yellow LED: Button 2 (Button 1 && Button 3)
   - Red LED: Button 3

2. The Arduino displays a sequence of LED lights, which the user must remember.

3. The user must press the corresponding buttons to replicate the displayed sequence.

4. After the user enters their sequence, the Arduino compares the user's sequence with the original sequence.
   - If the sequence is correct, the green LED blinks three times.
   - If the sequence is incorrect, the red LED blinks three times.

## How to Use

1. Connect the components following the provided connection diagram.
2. Upload the code to your Arduino Nano using the Arduino IDE.
3. Have fun playing and improving your sequential memory!

## Connection Diagram


## Contribution

Contributions are welcome. If you have ideas to improve the project, feel free to open an issue or send a pull request.

## Credits

This project was created by [Laureano Ivan Gerardo Vera]() as part of an Arduino learning exercise.

## License

This project is under the [License Name] License. For more details, see the LICENSE.md file.