#include "machinecontext.hpp"

auto startup(sdbusplus::async::context& ctx) -> sdbusplus::async::task<>
 {
    sdbusplus::server::manager_t manager{ctx, MachineContext::ReqDBusPath};

    ctx.request_name(MachineContext::ReqDBusInterface);
    co_return;
 }

int main()
{
    sdbusplus::async::context ctx;
    MachineContext c{ctx, MachineContext::ReqDBusPath};
 
    ctx.spawn(startup(ctx));
    ctx.run();

    return 0;
};
