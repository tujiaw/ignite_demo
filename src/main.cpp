#include <stdint.h>
#include <iostream>
#include <time.h>
#include "widget.h"
#include <thread>
#include "ignite/ignite.h"
#include "ignite/ignition.h"

using namespace ignite;
using namespace cache;
using namespace query;

typedef std::vector< CacheEntry<int64_t, Widget> > ResVector;

int main()
{
    IgniteConfiguration cfg;

    //cfg.springCfgPath = "platforms/cpp/examples/oper-example/config/oper-example.xml";
    cfg.jvmInitMem = 128;
    cfg.jvmMaxMem = 256;
    try
    {
        // Start a node.
        Ignite ignite = Ignition::Start(cfg);
        std::cout << "\n--------------------Start Successfully--------------------\n";

        std::set<int64_t> keys;
        {
            std::cout << "set data\n";
            
	    Cache<int64_t, Widget> cache = ignite.GetOrCreateCache<int64_t, Widget>("Widget");
            for (int i = 1; i <= 10; i++) {
                std::ostringstream ossName, ossContent;
                ossName << "name" << i;
                ossContent << "content" << i;
                cache.Put(i, Widget(i, ossName.str(), ossContent.str(), 100, 50));
                keys.insert(i);
            }
            
        }

        {

            std::cout << "get data\n";
            Cache<int64_t, Widget> cache = ignite.GetCache<int64_t, Widget>("Widget");
            auto widgets = cache.GetAll(keys);
            for (auto iter = widgets.begin(); iter != widgets.end(); ++iter) {
                std::cout << iter->second.toString() << std::endl;
            }

        }
        
        // Stop node.
        Ignition::StopAll(false);
    }
    catch (IgniteError& err)
    {
        std::cout << "An error occurred: " << err.GetText() << std::endl;
        std::cin.get();
        return err.GetCode();
    }

    std::cout << std::endl;
    std::cout << ">>> Example finished, press 'Enter' to exit ..." << std::endl;
    std::cout << std::endl;
    std::cin.get();
    return 0;
}

