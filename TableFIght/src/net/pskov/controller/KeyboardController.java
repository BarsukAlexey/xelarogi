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
            if (keyboard.poll()) {
                continue;
            }
            EventQueue keyboardQueue = keyboard .getEventQueue();
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


//package net.pskov;
//
//import net.java.games.input.*;
//
//import java.util.HashMap;
//
//public class KeyboardController {
//    public Keyboard m_keyboard;
//    EventQueue m_keyboardQueue;
//    public HashMap<Component.Identifier, Boolean> m_keyDown;
//
//    public KeyboardController() {
//        Controller[] inputDevices = ControllerEnvironment.getDefaultEnvironment().getControllers();
//        m_keyboard = null;
//        for (Controller c : inputDevices) {
//            if (c.getType() == Controller.Type.KEYBOARD) {
//                m_keyboard = (Keyboard) c;
//                break;
//            }
//        }
//        if (m_keyboard != null) {
//            m_keyDown = new HashMap<>();
//            for (Component c : m_keyboard.getComponents())
//                m_keyDown.put(c.getIdentifier(), false);
//
//        }
//    }
//
//    public void capture() {
//        if (m_keyboard == null)
//            return;
//
//        m_keyboard.poll();
//        m_keyboardQueue = m_keyboard.getEventQueue();
//        Event event = new Event();
//        while (m_keyboardQueue.getNextEvent(event)) {
//            float data = event.getComponent().getPollData();
//            if (data != 0.0f) {
//                Component.Identifier identifier = event.getComponent().getIdentifier();
//                m_keyDown.put(identifier, true);
//                System.err.println(identifier + " -> " + data);
//            } else {
//                m_keyDown.put(event.getComponent().getIdentifier(), false);
//            }
//        }
//    }
//
//}
