#include <bn_backdrop.h>
#include <bn_core.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>
#include <bn_music.h>


#include "bn_sprite_items_bun.h"

#define FLOOR (80 - 8)

int main() {
    bn::core::init();

    bn::backdrop::set_color(bn::color(15, 0, 0));

    auto dot = bn::sprite_items::bun.create_sprite(0, 0);

    bn::fixed speed = 1.5;
    bn::fixed dy = 0;
    bn::fixed gravity = .03;
    bn::fixed jump_strength = 1.2;

    // Values for the floor level
    int currentFloor = FLOOR;

    int horizontalLimit = 110;


    while(true) {

        if(bn::keypad::left_held()) {
            dot.set_x(dot.x() - speed);
            dot.set_horizontal_flip(false);
        }
        if(bn::keypad::right_held()) {
            dot.set_x(dot.x() + speed);
            dot.set_horizontal_flip(true);
        }
        if(bn::keypad::a_pressed() && dot.y() == currentFloor) {
            dy -= jump_strength;
        }

        // If the player touches the right horizontal limit, stop them
        if (dot.x() > horizontalLimit) {
            dot.set_x(horizontalLimit);
        }

        // If the player touches the left horizontal limit, stop them
         if (dot.x() < -horizontalLimit) {
            dot.set_x(-horizontalLimit);
        }

        if (bn::keypad::down_pressed()) {
            gravity = -gravity;
            dot.set_vertical_flip(!dot.vertical_flip());

            // If the current floor level is the floor for normal gravity, turn the floor into negative for inverse gravity, else
            // keep it as the normal floor
            currentFloor == FLOOR ? currentFloor = -FLOOR : currentFloor = FLOOR;
        }

        dy += gravity;

        dot.set_y(dot.y() + dy);

        // If the current floor level is for the normal gravity AND if we are more than the floor level, keep them at the floor level
        if(currentFloor == FLOOR && dot.y() > currentFloor) {
            dot.set_y(FLOOR);
            dy = 0;
        // If the current floor level is for inverse gravity AND we are less than the floor level, keep them stuck at the floor level
        } else if (currentFloor == -FLOOR && dot.y() < currentFloor){
            dot.set_y(-FLOOR);
            dy = 0;
        }

        bn::core::update();
    }
}