package net.pskov.controller;

import net.java.games.input.*;

import java.util.Arrays;
import java.util.HashSet;

public class KeyboardController {

    public Keyboard[] m_keyboard;

    public KeyboardController() {
        Controller[] inputDevices = ControllerEnvironment.getDefaultEnvironment().getControllers();
        m_keyboard = new Keyboard[0];
        for (Controller c : inputDevices) {
            if (c.getType() == Controller.Type.KEYBOARD) {
                m_keyboard = Arrays.copyOf(m_keyboard, m_keyboard.length + 1);
                m_keyboard[m_keyboard.length - 1] = (Keyboard) c;
            }
        }
    }

    public HashSet<Component.Identifier> capture() {
        HashSet<Component.Identifier> set = new HashSet<>();
        for (Keyboard keyboard : m_keyboard) {
            if (!keyboard.poll()) {
                continue;
            }
            EventQueue keyboardQueue = keyboard.getEventQueue();
            Event event = new Event();
            while (keyboardQueue.getNextEvent(event)) {
                float pollData = event.getComponent().getPollData();
                if (pollData != 0.0f) {
                    set.add(event.getComponent().getIdentifier());
                }
            }
        }
        return set;
    }
}