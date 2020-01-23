import asyncio
import websockets

async def recv_msg(websocket):
    while True:
        text = await websocket.recv()
        print(text)

async def main_logic(websocket, path):
    await recv_msg(websocket)

start_server = websockets.serve(main_logic, '127.0.0.1', 5678)
asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
