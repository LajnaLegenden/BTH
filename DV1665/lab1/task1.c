int fn(char args){
    char value = args;

    value -= 0x41;

    switch(value){
        case 0:
            value = 0x41;
            return value;
        case 1:
            value = 0x42;
            return value;
        case 2:
            value = 0x43;
            return value;
        default:
            value = 0x5A;
            return value;
    }
}