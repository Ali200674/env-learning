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

    auto dot = bn::sprite_items::bun.create_sprite(-20, 0);

    auto dot2 = bn::sprite_items::bun.create_sprite(20, 0);

    bn::fixed speed = 1.5;
    bn::fixed dy = 0;
    bn::fixed gravity = .03;
    bn::fixed jump_strength = 1.2;

    // Values for the floor level
    int currentFloor = FLOOR;

    int horizontalLimit = 110;

    dot2.set_vertical_flip(true);

    while(true) {        

        // If the user presses left, make the the normal bunny go left and the inverse bunny go right
        if(bn::keypad::left_held()) {
            dot.set_x(dot.x() - speed);
            dot.set_horizontal_flip(false);

            dot2.set_x(dot2.x() + speed);
            dot2.set_horizontal_flip(true);
        }

        // If the user presses right, make the the normal bunny go right and the inverse bunny go left
        if(bn::keypad::right_held()) {
            dot.set_x(dot.x() + speed);
            dot.set_horizontal_flip(true);

            dot2.set_x(dot2.x() - speed);
            dot2.set_horizontal_flip(false);
        }

        // If the user is on the floor level AND the user pressed x, make both bunnies jump
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
        
        // Same idea as above but for the inverse bunny
        if (dot2.x() > horizontalLimit) {
            dot2.set_x(horizontalLimit);
        }
        if (dot2.x() < -horizontalLimit) {
            dot2.set_x(-horizontalLimit);
        }

       

        
        // If the user pressed the down arrow key, invert the gravity, vertically flip the bunnies, and switch the current floor level
        if (bn::keypad::down_pressed()) {
            gravity = -gravity;

            dot.set_vertical_flip(!dot.vertical_flip());
            dot2.set_vertical_flip(!dot2.vertical_flip());

            // If the current floor level is the floor for normal gravity, turn the floor into negative for inverse gravity, else
            // keep it as the normal floor
            currentFloor == FLOOR ? currentFloor = -FLOOR : currentFloor = FLOOR;
        }

        dy += gravity;

        dot.set_y(dot.y() + dy);
        dot2.set_y(dot2.y() - dy);

        // If the current floor level is normal
        if (currentFloor == FLOOR) {

            // If the normal bunnies y level is more than the floor level, stop them and set dy to 0
            if (dot.y() > currentFloor) {
                dot.set_y(currentFloor);
                dy = 0;
            } 
            
            // Same thing as above, but for inverse bunny and floor is negative
            if (dot2.y() < -currentFloor) {
                dot2.set_y(-currentFloor);
                dy = 0;
            }
            
        } else { // Else, the floor is negative

            // If normal bunnies y level is less than floor level, stop them and set dy to 0
            if (dot.y() < currentFloor) {
                dot.set_y(currentFloor);
                dy = 0;
            } 


            // Same thing, but opposite as above
            if (dot2.y() > -currentFloor) {
                dot2.set_y(-currentFloor);
                dy = 0;
            } 
        }

        bn::core::update();
    }
}