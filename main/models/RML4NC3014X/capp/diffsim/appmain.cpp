#include "appmain.hpp"              // IWYU pragma: keep

#include "appmain_config.hpp"
#include "appmain_startup.hpp"


int main(int argc, char* argv[])
{
    int stage_return;

    // config stage
    if ((stage_return = config(argc, argv)))
        return stage_return;

    // startup stage
    if ((stage_return = startup()))
        return stage_return;
    
    
    

    // TODO


    shutdown();

    return 0;
}


