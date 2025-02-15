#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

// Button Press Test
bool button_press(Event& event, Vector2f  pos, RectangleShape key)
{
    if (key.getGlobalBounds().contains(pos.x, pos.y)
        && event.type == Event::MouseButtonPressed
        && event.key.code == Mouse::Left) {
        return true;
    }
    return false;
}


// Clearing button presses
void button_clear(RectangleShape& button1, RectangleShape& button2, RectangleShape& button3,
    RectangleShape& button4, RectangleShape& button5)
{
    button1.setFillColor(Color(105, 105, 105));
    button2.setFillColor(Color(105, 105, 105));
    button3.setFillColor(Color(105, 105, 105));
    button4.setFillColor(Color(105, 105, 105));
    button5.setFillColor(Color(105, 105, 105));
}


// Creating a Button
void button_create(RectangleShape& button, float a, float b)
{
    button.setSize(Vector2f(70, 70));
    button.setPosition(a, b);
    button.setFillColor(Color(105, 105, 105));
}


// Creating text
void text_create(Text& text, string name, float a, float b)
{
    text.setCharacterSize(60);
    text.setFillColor(Color(220, 220, 220));
    text.setString(name);
    text.setPosition(a, b);
}


// Action Index
void text_pointer(Data number, Text& text, string name)
{   
    double ideal_value, lowest_value, highest_value;
    int check = 0;
    if (name == "E1") { 
        ideal_value = 328.0;
        lowest_value = 300.0;
        highest_value = 340.0;
    }
    else if (name == "H") { 
        ideal_value = 247.0;
        lowest_value = 210.0;
        highest_value = 260.0;
    }
    else if (name == "G") { 
        ideal_value = 196.0;
        lowest_value = 180.0;
        highest_value = 220.0;
    }
    else if (name == "D") { 
        ideal_value = 146.83;
        lowest_value = 130.0;
        highest_value = 170.0;
    }
    else if (name == "A") { 
        ideal_value = 110.0;
        lowest_value = 90.0;
        highest_value = 130.0;
    }
    else if (name == "E2") { 
        ideal_value = 83.0;
        lowest_value = 60.0;
        highest_value = 100.0;
    }
    else { 
        ideal_value = 0.0;
        lowest_value = 0.0;
        highest_value = 0.0;
    }

    if ((number.value > highest_value)
        || (number.value < lowest_value))
    {check = 1;}
    else check = 0;
    
    if ((name != "") && (check != 1))
    {
        if ((number.value > (ideal_value + 9.0))) {
            text.setString("Lower"); 
        }
        else if ((number.value <= (ideal_value + 9.0)) 
            && (number.value > (ideal_value + 3.0))) { 
            text.setString("Good(Lower)"); 
        }
        else if ((number.value <= (ideal_value + 3.0))
            && (number.value >= (ideal_value - 3.0))) {
            text.setString("Amazing"); 
        }
        else if ((number.value >= (ideal_value - 9.0)) 
            && (number.value < (ideal_value - 3.0))) { 
            text.setString("Good(Higher)"); 
        }
        else if (number.value < (ideal_value - 9.0)) { 
            text.setString("Higher"); 
        }
    }
}
