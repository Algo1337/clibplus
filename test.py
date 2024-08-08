import asyncio, telnetlib3

async def shell(reader, writer):
    writer.write("Welcome to BOATNET NIGGA! ")
    while True:
        writer.write('Skidder@Net # ~ ')
        inp = await reader.read(1)
        if inp:
            writer.echo(inp)
            print(f"{inp}")
            if inp == "TEST":
                writer.write("Works\r\n")
            writer.write('\r\nThey say the only way to win '
                        'is to not play at all.\r\n')
            
    await writer.drain()
    writer.close()

loop = asyncio.get_event_loop()
coro = telnetlib3.create_server(port=6023, shell=shell)
server = loop.run_until_complete(coro)
loop.run_until_complete(server.wait_closed())