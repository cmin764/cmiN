import asyncio


async def waiter(event):
    print("waiting for it ...")
    await event.wait()
    print("... got it!")
    await asyncio.sleep(2)


async def main():
    # Create an Event object.
    event = asyncio.Event()

    # Spawn a Task to wait until 'event' is set.
    waiter_task = asyncio.create_task(waiter(event))

    # Sleep for 1 second and set the event.
    print("aaaa")
    await asyncio.sleep(1)
    event.set()

    # Wait until the waiter task is finished.
    print("bbbbb")
    await waiter_task
    print("finished")


asyncio.run(main())
