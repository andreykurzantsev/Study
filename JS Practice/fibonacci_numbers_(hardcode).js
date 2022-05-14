"use strict";

function fib(a) {

    let blank = "0 1";

    if (!Number.isInteger(a) || typeof a != 'number' || a <= 0) {

        blank = "";
        return blank;

    } else if (a == 1) {

        blank = "0";
        return blank;

    } else if (a == 2) {

        return blank;

    } else {
        
        blank = "0 1";
        let fibvar1 = 0;
        let fibvar2 = 0;
        let fibfin = 0;
        for (let i = 0; i < 2 * a - 4; i++) {
            if (i % 2 === 0) {
                blank += " ";
            } else {
                fibvar1 = Number(blank.slice(i - 1, i));
                fibvar2 = Number(blank.slice(i + 1, i + 2));
                fibfin = fibvar1 + fibvar2;
                blank += fibfin;
            }

        }
        return blank;
    }

}
console.log(fib(4));