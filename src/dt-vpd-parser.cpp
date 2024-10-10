#include "machinecontext.hpp"

int main()
{
    sdbusplus::async::context ctx;
	
    sdbusplus::server::manager_t manager{ctx, MachineContext::ReqDBusPath};
    MachineContext c{ctx, MachineContext::ReqDBusPath};
	
    ctx.spawn([](sdbusplus::async::context& ctx) -> sdbusplus::async::task<> {
            ctx.request_name(MachineContext::ReqDBusInterface);
            co_return;
        }(ctx));

    ctx.run();

    return 0;
};
