#pragma once
#define WB 90
#define HB 7
const char BANNER[HB][WB]{ "   :=++++++= .=+++++=       :+++.   --    :++-   .-    -+++=  =    -:    =++: ",
						   "  #@@@%%%#-.+%%@@@#-      =%@@@@: -%@@%-  +@@# :#@*  =%@@#- +@@  +@@@#-  #@@= ",
                           " .@@@=-.      -@@#      +@@@%@@@: #@@@@@@+*@@# *@@#+@@@*:   @@@  @@@@@@%=%@@= ",
                           "  -%@@@@%:    -@@#   .+@@@#: %@@: #@@=:#@@@@@# *@@@@@@%.    @@@  @@@:-%@@@@@= ",
                           "     .+@@#    -@@#  +@@@*+#%%@@@: #@@=  :*@@@# *@@@*+@@@#   @@@  @@@:  -#@@@= ",
                           " -@@@@@@%:    -@@#  #@+:=++++@@@: #@@=    .+@# *@@*   =%@   @@@  @@@:    :*@= ",
                           " .-----:      .--:  :        ---  :--.       : :--:     :   ---  ---        . \n"};
#define HELLO "\nWelcome to the program for numerical integration.\nProject of the IDB-23-12 group on OOP.\n\n"

#define HOW_TO_USE "To use the program, you need to enter a mathematical expression, interval,\ncalculation method and the accuracy you want to obtain.\n\n"

#define AUTHORS "Authors of the program:\n"
#define BOLOGOV    "\t*Bologov V.D. Lead, programmer.\n"
#define PERINNIKOV "\t*Perinnikov G.A. Analist, programmer.\n"
#define KOLYADIN   "\t*Kolyadin I.A. Programmer.\n"
#define KUSKOV     "\t*Kuskov A.A. Tester.\n"
#define SINEV      "\t*Sinev D.A. Analist.\n\n"
#define NEXT_STEP "Press any key to start working..."

#define WI 10
#define HI 5
const char INTEGRAL[HI][WI] = {"   ##\n",
                               "  #\n  ",
                               "  #\n  ",
                               "  #\n  ",
                               "##\n   " };

#define INTERVAL "Enter interval: "
#define SELECT_METHOD "Select method: "
#define METHOD_LR     "\n\t*[LR] Left Rienman\n"
#define METHOD_RR     "\t*[RR] Right Rienman\n"
#define METHOD_MR     "\t*[MR] Middle Rienman\n"
#define METHOD_TR     "\t*[TR] Trapeze\n"
#define METHOD_SI     "\t*[SI] Simpson\n\n"


#define PRESICION "What calculation presicion are you want: "

#define CONTINUE "\n\nDo you want to continue? [y/n]: "
