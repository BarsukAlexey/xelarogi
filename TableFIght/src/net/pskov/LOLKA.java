package net.pskov;

import java.io.File;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class LOLKA {

    public static void main(String[] args) {
        System.err.println(new SimpleDateFormat("HH'h'mm'm' dd.MM.yyyy").format(Calendar.getInstance().getTime()));
        System.err.println(Calendar.getInstance().getTime());
        System.err.println(Calendar.getInstance().getTimeZone());
    }
}
