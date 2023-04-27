#include <base/component.h>
#include <base/log.h>
#include <timer_session/connection.h>
namespace Hello { struct Main; }
struct Hello::Main
{
Genode::Env &_env;
Timer::Connection _timer { _env };
void _handle_timeout()
{
Genode::log("woke up at ", _timer.elapsed_ms(), " ms");
}
Genode::Signal_handler<Main> _timeout_handler {
_env.ep(), *this, &Main::_handle_timeout };
Main(Genode::Env &env) : _env(env)
{
_timer.sigh(_timeout_handler);
_timer.trigger_periodic(1000*1000*5);
Genode::log("component constructed");
}
};
void Component::construct(Genode::Env &env)
{
static Hello::Main main(env);
}
