#ifndef __MSG__
#define __MSG__

#include <Arduino.h>


/**
 * Class representing a message in a communication.
*/
class Msg {
private:
    String content;

public:
    /**
     * Create a new message with the given content.
     * @param content the content of the message.
    */
    Msg(String content) {
        this->content = content;
    }

    /**
     * Get the content of the message.
     * @return the content of the message
    */
    String getcontent() {
        return this->content;
    }
};

#endif
