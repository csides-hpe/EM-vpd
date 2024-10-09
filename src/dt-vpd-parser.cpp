#include "machinecontext.hpp"

int main()
{
    sdbusplus::async::context ctx;

    sdbusplus::server::manager_t manager{ctx, MachineContext::dbus_object_path};

    MachineContext c{ctx, MachineContext::dbus_object_path};
    ctx.spawn([](sdbusplus::async::context& ctx) -> sdbusplus::async::task<> {
        ctx.request_name(MachineContext::dbus_interface);
        co_return;
    }(ctx));

    ctx.run();

    return 0;
};
