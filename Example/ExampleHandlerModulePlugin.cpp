/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "ExampleHandlerModulePlugin.h"
#include "CoreRegistry.h"
#include "HandlerManager.h"
#include "InputStreamManager.h"
#include "ExampleStreamHandler.h"
#include "MockInputStream.h"
#include <Corrade/PluginManager/AbstractManager.h>
#include <nlohmann/json.hpp>

CORRADE_PLUGIN_REGISTER(VisorHandlerExample, visor::handler::example::ExampleHandlerModulePlugin,
    "visor.module.handler/1.0")

namespace visor::handler::example {

using namespace visor::input::mock;
using json = nlohmann::json;

void ExampleHandlerModulePlugin::setup_routes([[maybe_unused]]HttpServer *svr)
{
}
std::unique_ptr<StreamHandler> ExampleHandlerModulePlugin::instantiate(const std::string &name, InputStream *input_stream, const Configurable *config)
{
    // TODO using config as both window config and module config
    auto handler_module = std::make_unique<ExampleStreamHandler>(name, input_stream, config);
    return handler_module;
}

}