/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#pragma once

#include "AbstractMetricsManager.h"
#include "MockInputStream.h"
#include "StreamHandler.h"
#include <Corrade/Utility/Debug.h>
#include <limits>
#include <spdlog/spdlog.h>
#include <string>

namespace visor::handler::example {

using namespace visor::input::mock;

class ExampleMetricsBucket final : public visor::AbstractMetricsBucket
{

protected:
    mutable std::shared_mutex _mutex;

    // total numPackets is tracked in base class num_events
    struct counters {

        Counter mock_counter;

        counters()
            : mock_counter("example", {"counter"}, "Count of random ints from mock input source")
        {
        }
    };
    counters _counters;

public:
    ExampleMetricsBucket()
    {
    }

    // get a copy of the counters
    counters counters() const
    {
        std::shared_lock lock(_mutex);
        return _counters;
    }

    // visor::AbstractMetricsBucket
    void specialized_merge(const AbstractMetricsBucket &other) override;
    void to_json(json &j) const override;
    void to_prometheus(std::stringstream &out, Metric::LabelMap add_labels = {}) const override;

    void process_random_int(uint64_t i);
};

class ExampleMetricsManager final : public visor::AbstractMetricsManager<ExampleMetricsBucket>
{
public:
    ExampleMetricsManager(const Configurable *window_config)
        : visor::AbstractMetricsManager<ExampleMetricsBucket>(window_config)
    {
    }

    void process_random_int(uint64_t i);
};

class ExampleStreamHandler final : public visor::StreamMetricsHandler<ExampleMetricsManager>
{

    MockInputStream *_mock_stream;
    std::shared_ptr<spdlog::logger> _logger;

    sigslot::connection _random_int_connection;

    void process_random_int(uint64_t i);

public:
    ExampleStreamHandler(const std::string &name, InputStream *stream, const Configurable *window_config, StreamHandler *handler = nullptr);
    ~ExampleStreamHandler();

    // visor::AbstractModule
    std::string schema_key() const override
    {
        return "example";
    }

    size_t consumer_count() const override
    {
        return 0;
    }

    void start() override;
    void stop() override;
};

}
