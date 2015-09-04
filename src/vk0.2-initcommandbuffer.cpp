/*
 * Vulkan Samples Kit
 *
 * Copyright (C) 2015 LunarG, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*
VULKAN_SAMPLE_SHORT_DESCRIPTION
Create Vulkan command buffer
*/

#include <util_init.hpp>
#include <assert.h>
#include <cstdlib>

int main(int argc, char **argv)
{
    VkResult U_ASSERT_ONLY res;
    struct sample_info info = {};
    char sample_title[] = "Command Buffer Sample";

    init_global_layer_properties(info);
    info.instance_extension_names.push_back(VK_WSI_SWAPCHAIN_EXTENSION_NAME);
    info.device_extension_names.push_back(VK_WSI_DEVICE_SWAPCHAIN_EXTENSION_NAME);
    init_instance(info, sample_title);
    init_enumerate_device(info);
    init_device(info);
    info.width = info.height = 500;
    init_connection(info);
    init_window(info);
    init_wsi(info);

    /* VULKAN_KEY_START */

    /* Create a command pool to allocate our command buffer from */
    VkCmdPoolCreateInfo cmd_pool_info = {};
    cmd_pool_info.sType = VK_STRUCTURE_TYPE_CMD_POOL_CREATE_INFO;
    cmd_pool_info.pNext = NULL;
    cmd_pool_info.queueFamilyIndex = info.graphics_queue_family_index;
    cmd_pool_info.flags = 0;

    res = vkCreateCommandPool(info.device, &cmd_pool_info, &info.cmd_pool);
    assert(!res);

    /* Create the command buffer from the command pool */
    VkCmdBufferCreateInfo cmd = {};
    cmd.sType = VK_STRUCTURE_TYPE_CMD_BUFFER_CREATE_INFO;
    cmd.pNext = NULL;
    cmd.cmdPool = info.cmd_pool;
    cmd.level = VK_CMD_BUFFER_LEVEL_PRIMARY;
    cmd.flags = 0;

    res = vkCreateCommandBuffer(info.device, &cmd, &info.cmd);
    assert(!res);

    /* VULKAN_KEY_END */

    vkDestroyCommandBuffer(info.device, info.cmd);
    vkDestroyCommandPool(info.device, info.cmd_pool);
    vkDestroyDevice(info.device);
    vkDestroyInstance(info.inst);
    destroy_window(info);
}
