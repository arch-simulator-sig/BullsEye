#include "appmain_config.hpp"
//
// Configuration procedures
//
//

#include "appmain_glbl.hpp"


#include <iostream>
#include <sstream>


int config(int argc, char* argv[])
{
    // binary file name
    std::ostringstream argoss;
    for (int i = 1; i < argc; i++)
        argoss << argv[i] << " ";

    if (argoss.view().empty())
    {
        std::cout << "[\033[1;31mERROR\033[0m] Binary file path required." << std::endl;
        return 1;
    }

    std::string binaryfilename = argoss.str();
    binaryfilename.pop_back();

    glbl.cfg.binaryFileName = binaryfilename;


    // dump 0
    glbl.cfg.dump0.enabled = true;

    glbl.cfg.dump0.upperCount = 3;
    glbl.cfg.dump0.lowerCount = 3;

    glbl.cfg.dump0.muteUnread = true;


    // dump 1
    glbl.cfg.dump1.enabled = true;

    glbl.cfg.dump1.upperCount = 8;
    glbl.cfg.dump1.lowerCount = 1;

    glbl.cfg.dump1.displayTrace = true;

    glbl.cfg.dump1.muteUnread = true;


    // dump 2
    glbl.cfg.dump2.enabled = true;

    glbl.cfg.dump2.depth = 7;


    // dump 3
    glbl.cfg.dump3.enabled = false;

    glbl.cfg.dump3.depth = 7;


    // dump 4
    glbl.cfg.dump4.enabled = true;

    glbl.cfg.dump4.depth = 7;


    //

    return 0;
}
