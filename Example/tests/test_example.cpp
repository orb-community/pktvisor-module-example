#include <catch2/catch.hpp>

#include "ExampleStreamHandler.h"
#include "MockInputStream.h"

using namespace visor::handler::example;
using namespace visor::input::mock;

TEST_CASE("Parse net (dns) UDP IPv4 tests", "[pcap][net]")
{

    MockInputStream stream{"mock-test"};

    visor::Config c;
    c.config_set<uint64_t>("num_periods", 1);
    auto stream_proxy = stream.add_event_proxy(c);
    ExampleStreamHandler example_handler{"example-test", stream_proxy, &c};

    example_handler.start();
    stream.start();
    example_handler.stop();
    stream.stop();

    auto counters = example_handler.metrics()->bucket(0)->counters();
    auto event_data = example_handler.metrics()->bucket(0)->event_data_locked();

    CHECK(example_handler.metrics()->current_periods() == 1);

    CHECK(example_handler.metrics()->bucket(0)->period_length() == 0);

    CHECK(event_data.num_events->value() == 0);
    CHECK(counters.mock_counter.value() == 0);
}
