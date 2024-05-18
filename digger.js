var really_secret_keyword = 'hahaism'
var version = '1.16.5'

mineflayer = require('mineflayer')
pathfinder = require('mineflayer-pathfinder').pathfinder
v = require('vec3')
GoalNear = require('mineflayer-pathfinder').goals.GoalNear
AutoAuth = require('mineflayer-auto-auth')
toolplugin = require('mineflayer-tool').plugin
mineflayerViewer = require('prismarine-viewer').mineflayer
mcData = require('minecraft-data')(version)

specify_blocks = [
    mcData.blocksByName.water.id,
    mcData.blocksByName.lava.id,
    mcData.blocksByName.air.id
]

build_block_item_id = mcData.itemsByName.cobblestone.id


function getCuboid(v1, v2) {
    let blocks = [];

    min_x = Math.min(v1.x, v2.x)
    max_x = Math.max(v1.x, v2.x)

    min_y = Math.min(v1.y, v2.y)
    max_y = Math.max(v1.y, v2.y)

    min_z = Math.min(v1.z, v2.z)
    max_z = Math.max(v1.z, v2.z)

    for (let y = max_y; y >= min_y; y--) {
        for (let x = min_x; x <= max_x; x++) {
            for (let z = min_z; z <= max_z; z++) {
                blocks.push(v(x, y, z))
            }
        }
    }
    return blocks;
}

const bot = mineflayer.createBot({
    host: 'localhost',
    port: 62784,
    username: 'durashka',
    plugins: [AutoAuth, pathfinder, toolplugin],
    auth: 'offline',
    AutoAuth: '123123'
    // AutoAuth: {
    //   logging: true,
    //   password: '12321',
    //   ignoreRepeat: true
    // }
})

async function dig(v1, v2) {
    let cuboid = getCuboid(v1, v2)
    for (var a = 0; a < cuboid.length; a++) {


        let pos = cuboid[a]
        block = bot.blockAt(v(pos.x, pos.y, pos.z))

        if (specify_blocks.includes(block.type)) {
            continue
        }
        movements = new Movements(bot, mcData);

        bot.pathfinder.setMovements(movements);
        bot.pathfinder.setGoal(new GoalNear(pos.x, pos.y, pos.z, 3));

        while (true) {
            try {
                bot.tool.equipForBlock(block)
                break
            } catch (e) {

            }
        }

        await bot.dig(bot.blockAt(pos))
    }
}

async function go(v) {
    await bot.pathfinder.goto(new GoalNear(v.x, v.y, v.z, 1))
}

// async function place_blocks(v1, v2) {

//     let sourcePosition = bot.entity.position.offset(0, -1.5, 0);
//     let sourceBlock = bot.blockAt(sourcePosition);
    
//     let faceVector = {x:5, y:0, z:0};

//     await bot.placeBlock(sourceBlock, faceVector);
//     return

//     new_v = new v(0, 1, 0)
//     const cobblestone = bot.inventory.findInventoryItem(build_block_item_id, null)
//     bot.equip(cobblestone, 'hand')
//     console.log(bot.blockAt(bot.entity.position))
//     await bot.placeBlock(bot.blockAt(bot.entity.position), {x: 2, y:2, z: 0})
//     return


//     let cuboid = getCuboid(v1, v2).reverse()
//     for (var a = 0; a < cuboid.length; a++) {
//         let pos = cuboid[a]
//         block = bot.blockAt(v(pos.x, pos.y, pos.z))

//         if (!specify_blocks.includes(block.type)) {
//             continue
//         }

//         await bot.pathfinder.goto(new GoalNear(pos.x, pos.y, pos.z, 1))

//         const cobblestone = bot.inventory.findInventoryItem(build_block_item_id, null)
        
//         if (cobblestone == null) {
//             console.log('pipec')
//             return
//         }
//         bot.equip(cobblestone, 'hand')


//         bot_pos = bot.entity.position
        
//         if (bot_pos.x > pos.x){
//             x = -1
//         } else {
//             x = 1
//         }

//         if (bot_pos.z > pos.z){
//             z = -1
//         } else {
//             z = 1
//         }

//         if (bot_pos.y > pos.y){
//             y = -1
//         } else {
//             y = 1
//         }


        
//         new_v = new v(x, y, z)
//         await bot.placeBlock(cobblestone, new_v)
//     }
// }

bot.on('whisper', async function (sender, message) {
    // signature: <secret key word> <command> <args...>
    message = message.split(' ')

    console.log(message)

    if (message[0] == really_secret_keyword) {
        if (message[1] == 'dig') {
            // <x1> <y1> <z1> <x2> <y2> <z2>
            v1 = v(parseInt(message[2]),
                parseInt(message[3]),
                parseInt(message[4])
            )
            v2 = v(parseInt(message[5]),
                parseInt(message[6]),
                parseInt(message[7]))
            dig(v1, v2)
        // } else if (message[1] == 'place') {
        //         // <x1> <y1> <z1> <x2> <y2> <z2>
        //         v1 = v(parseInt(message[2]),
        //             parseInt(message[3]),
        //             parseInt(message[4])
        //         )
        //         v2 = v(parseInt(message[5]),
        //             parseInt(message[6]),
        //             parseInt(message[7]))
        //         place_blocks(v1, v2)
        } else if (message[1] == 'warp') {
            // <warp-name>
            bot.chat(`/warp ${message[2]}`)
        } else if (message[1] == 'go') {
            // no args
            go(bot.players[sender].entity.position)

        }
    }
})
