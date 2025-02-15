#include <iostream>
#include <vector>
#include <fftw3.h>
#include <portaudio.h>
#include <SFML/Graphics.hpp>
#include "sound.h"
#include "interface.h"

// Options for recording audio
#define SAMPLE_RATE (48000)
#define FRAMES_PER_BUFFER (17824)

using namespace std;
using namespace sf;


int main() 
{
    Data data;

    // Troubleshooting and launch
    PaError error;
    error = Pa_Initialize();
    if (error != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(error) << endl;
        return 1;
    }

    PaStream* stream;
    error = Pa_OpenDefaultStream(&stream, 1, 0, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, audio_callback, &data);
    if (error != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(error) << endl;
        Pa_Terminate();
        return 1;
    }

    error = Pa_StartStream(stream);
    if (error != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(error) << endl;
        Pa_CloseStream(stream);
        Pa_Terminate();
        return 1;
    }

    cout << "Recording started. Press Enter to stop and exit." << endl;
    
    // Interface setup
    Image image;
    image.loadFromFile("display/background.jpg");

    Texture texture;
    texture.loadFromImage(image);

    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(-150, 0);

    RectangleShape button1, button2, button3, button4, button5, button6;
    button_create(button1, 100, 425);
    button_create(button2, 200, 425);
    button_create(button3, 300, 425);
    button_create(button4, 400, 425);
    button_create(button5, 500, 425);
    button_create(button6, 600, 425);

    Text text1, text2, text3, text4, text5, text6, text_direction;
    text_create(text1, "E", 100, 421);
    text_create(text2, "H", 200, 421);
    text_create(text3, "G", 300, 421);
    text_create(text4, "D", 400, 421);
    text_create(text5, "A", 500, 421);
    text_create(text6, "E", 600, 421);
    text_create(text_direction, "Select string and play", 100, 100);

    Font font;
    font.loadFromFile("display/Bahnschrift.ttf");
    text1.setFont(font);
    text2.setFont(font);
    text3.setFont(font);
    text4.setFont(font);
    text5.setFont(font);
    text6.setFont(font);
    text_direction.setFont(font);
    text_direction.setCharacterSize(40);

    Clock clock;

    string selected_name = "";
    RenderWindow window(VideoMode(800, 600), "My window");

    // Window output
    while (window.isOpen())
    {
        Vector2i mouse = Mouse::getPosition(window);
        Vector2f mouse_pos = window.mapPixelToCoords(mouse);

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        time = time / 800;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear();

        if (button_press(event, mouse_pos, button1)) {
            selected_name = "E1";
            button1.setFillColor(Color(255, 2, 2));
            button_clear(button2, button3, button4, button5, button6);
        }

        else if (button_press(event, mouse_pos, button2)) {
            selected_name = "H";
            button2.setFillColor(Color(255, 2, 2));
            button_clear(button1, button3, button4, button5, button6);
        }

        else if (button_press(event, mouse_pos, button3)) {
            selected_name = "G";
            button3.setFillColor(Color(255, 2, 2));
            button_clear(button1, button2, button4, button5, button6);
        }

        else if (button_press(event, mouse_pos, button4)) {
            selected_name = "D";
            button4.setFillColor(Color(255, 2, 2));
            button_clear(button1, button2, button3, button5, button6);
        }

        else if (button_press(event, mouse_pos, button5)) {
            selected_name = "A";
            button5.setFillColor(Color(255, 2, 2));
            button_clear(button1, button2, button3, button4, button6);
        }

        else if (button_press(event, mouse_pos, button6)) {
            selected_name = "E2";
            button6.setFillColor(Color(255, 2, 2));
            button_clear(button1, button2, button3, button4, button5);
        }

        text_pointer(data, text_direction, selected_name);

        window.draw(sprite);

        window.draw(button1);
        window.draw(button2);
        window.draw(button3);
        window.draw(button4);
        window.draw(button5);
        window.draw(button6);

        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.draw(text4);
        window.draw(text5);
        window.draw(text6);
        window.draw(text_direction);

        window.display();
    }

    // Ending a thread
    cin.get();
    error = Pa_StopStream(stream);
    if (error != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(error) << endl;
    }

    Pa_CloseStream(stream);
    Pa_Terminate();

    return 0;
}
