local inspect = require 'scripts/Chat/inspect'

x = 100

--[[t = {1, 2, 5, 77, "haha"}

for key, value in pairs(t) do
	print(key, value)
end]]--

function onEnable()
	print("enable script Chat")

	--cScript.registerEvent(EVENTS.CONNECT, onConnect)
	--cScript.registerEvent(EVENTS.DISCONNECT, onDisconnect)
	--cScript.registerEvent(EVENTS.MESSAGE, onMessage)
end

function onDisable()
	print("disable script Chat")
end

function onConnect(Client)
	cServer:broadcast("+ " .. Client:getUsername() .. " connected")
	return false --do not cancel event
end

function onDisconnect(Client)
	cServer:broadcast("- " .. Client:getUsername() .. " disconnected")
	return false --do not cancel event
end

function onMessage(EventMessage)
	print("[CHAT LUA] x=" .. x)
	print("[CHAT LUA] " .. inspect(getmetatable(EventMessage)))
	print("[CHAT LUA] username: " .. EventMessage:getClient():getUsername() .. " / message: " .. EventMessage:getMessage())
	print("[CHAT LUA] user inet adress: " .. EventMessage:getClient():getInetAdress())
	return false --do not cancel event
end