package net.pskov.controller;

import net.java.games.input.Mouse;

public class MouseController {
    private Mouse mouse;
    private boolean isPressedLeft;
    private boolean isPressedRight;

    private boolean wasLeftClick;
    private boolean wasRightClick;

    public MouseController(Mouse mouse) {
        this.mouse = mouse;
    }

    public boolean wasLeftClick() {
        return wasLeftClick;
    }

    public boolean wasRightClick() {
        return wasRightClick;
    }


    public boolean update() {

        wasLeftClick = wasRightClick = false;

        boolean isValid = mouse.poll();
        if (!isValid)
            return false;

        {
            float val = mouse.getLeft().getPollData();
            if (isPressedLeft && (val == 0)) {  // button released
                isPressedLeft = false;
            } else if (!isPressedLeft && (val == 1)) {  // button pressed
                isPressedLeft = true;
                wasLeftClick = true;
            }
        }

        {
            float val = mouse.getRight().getPollData();
            if (isPressedRight && (val == 0)) {  // button released
                isPressedRight = false;
            } else if (!isPressedRight && (val == 1)) {// button pressed
                isPressedRight = true;
                wasRightClick = true;
            }
        }
        return true;
    }


}
