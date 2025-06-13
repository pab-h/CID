#include <Arduino.h>

namespace entity {

    class Reference {
        
        public:
        
            uint     howLong;
            uint16_t atAngle; 

            Reference(uint howLong, uint16_t atAngle);

    };

}
