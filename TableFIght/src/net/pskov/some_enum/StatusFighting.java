package net.pskov.some_enum;

public enum StatusFighting {


    notBegin {
        @Override
        public String toString() {
            return "NOT START";
        }
    },

    /**
     * Идёт бой
     */
    fighting {
        @Override
        public String toString() {
            return "FIGHT!";
        }
    },


    /**
     * Идёт бой, но его остановили. Например чтобы поправить шлем, каску и т.д.
     */
    fightingPause {
        @Override
        public String toString() {
            return "FIGHT! - PAUSE";
        }
    },

    /**
     * Пауза, бойцы отдыхают
     */
    _break {
        @Override
        public String toString() {
            return "BREAK";
        }
    },


    /**
     * Дисквалификация
     */
    disqualification {
        @Override
        public String toString() {
            return "Disqualification!";
        }
    },

    /**
     * Бой закончен, но образовалась ничья. Один из судей должен сделать выбор в пользу одного из бойцов
     */
    finishTie {
        @Override
        public String toString() {
            return "Tie . . .";
        }
    },

    /**
     * Бой закончен, победитель определён, но главный судья может надавать Minus, Fo или Ex какому-нибудь из бойцов
     * (возможно даже победителю) и тогда этого бойца дисквалифицируют
     */
    finishPending {
        @Override
        public String toString() {
            return "FINISH";
        }
    },
}