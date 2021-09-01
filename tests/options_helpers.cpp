#include "options_helpers.h"

#include "options.h"
#include "weather.h"

override_option::override_option( const std::string &option, const std::string &value ) :
    option_( option )
{
    options_manager::cOpt &opt = get_options().get_option( option_ );
    old_value_ = opt.getValue( true );
    opt.setValue( value );
}

override_option::~override_option()
{
    get_options().get_option( option_ ).setValue( old_value_ );
}

scoped_weather_override::scoped_weather_override( const weather_type_id &weather )
{
    get_weather().weather_override = weather;
}

void scoped_weather_override::with_windspeed( const int windspeed_override )
{
    weather_manager &weather = get_weather();
    weather.windspeed_override = windspeed_override;
    weather.update_weather();
}

void scoped_weather_override::with_wind_direction( const int wind_direction_override )
{
    weather_manager &weather = get_weather();
    weather.wind_direction_override = wind_direction_override;
    weather.update_weather();
}

scoped_weather_override::~scoped_weather_override()
{
    weather_manager &weather = get_weather();
    weather.weather_override = WEATHER_NULL;
    weather.windspeed_override.reset();
    weather.update_weather();
}
