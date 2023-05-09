/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "ExampleStreamHandler.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace visor::handler::example {

ExampleStreamHandler::ExampleStreamHandler(const std::string &name, InputEventProxy *proxy, const Configurable *window_config)
    : visor::StreamMetricsHandler<ExampleMetricsManager>(name, window_config)
    , db(nullptr)
{
    assert(proxy);
    _logger = spdlog::get("dyn-example-handler");
    if (!_logger) {
        _logger = spdlog::stderr_color_mt("dyn-example-handler");
    }
    assert(_logger);
    // figure out which input stream we have
    _mock_proxy = dynamic_cast<MockInputEventProxy *>(proxy);
    if (!_mock_proxy) {
        throw StreamHandlerException(fmt::format("ExampleStreamHandler: unsupported input stream {}", proxy->name()));
    }
    _logger->info("example handler created");
}
ExampleStreamHandler::~ExampleStreamHandler()
{
    _logger->info("example handler destroyed");
}

void ExampleStreamHandler::process_random_int(uint64_t i)
{
    _logger->info("example handler received random int signal: {}", i);
    _metrics->process_random_int(i);
}

void ExampleStreamHandler::start()
{
    if (_running) {
        return;
    }

    _logger->info("mock handler start()");

    _random_int_connection = _mock_proxy->random_int_signal.connect(&ExampleStreamHandler::process_random_int, this);

    _running = true;
}

void ExampleStreamHandler::stop()
{
    if (!_running) {
        return;
    }

    _logger->info("example handler stop()");

    _running = false;
}

void ExampleMetricsBucket::specialized_merge(const AbstractMetricsBucket &o, [[maybe_unused]] Metric::Aggregate agg_operator)
{
    // static because caller guarantees only our own bucket type
    const auto &other = static_cast<const ExampleMetricsBucket &>(o);

    std::shared_lock r_lock(other._mutex);
    std::unique_lock w_lock(_mutex);

    _counters.mock_counter += other._counters.mock_counter;
}

void ExampleMetricsBucket::to_prometheus(std::stringstream &out, Metric::LabelMap add_labels) const
{
    std::shared_lock r_lock(_mutex);

    _counters.mock_counter.to_prometheus(out, add_labels);
}

void ExampleMetricsBucket::to_opentelemetry(metrics::v1::ScopeMetrics &scope, timespec &start_ts, timespec &end_ts, Metric::LabelMap add_labels) const
{
    std::shared_lock r_lock(_mutex);

    _counters.mock_counter.to_opentelemetry(scope, start_ts, end_ts, add_labels);
}

void ExampleMetricsBucket::to_json(json &j) const
{
    std::shared_lock r_lock(_mutex);

    _counters.mock_counter.to_json(j);
}
void ExampleMetricsBucket::process_random_int(uint64_t i)
{
    std::unique_lock w_lock(_mutex);
    _counters.mock_counter += i;
}

void ExampleMetricsManager::process_random_int(uint64_t i)
{
    live_bucket()->process_random_int(i);
}
}