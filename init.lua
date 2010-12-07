windows = {}

main_win = Window(0, 0, "Main Menu")
main_win.border = false
main_win.draggable = false

close_but = Button("Quit", 100)
close_but.onClick = function(self)
  os.exit()
end

windows[main_win] = true

panel = VerticalPanel()
label2 = Label("Current player:", 100)
player = Label("Player 1", 100)

panel:add(label2)
panel:add(player)
panel:add(close_but)

main_win:add(panel)
main_win:pack()


-- Game

field_color = Point4f(0, 0, 0, 0.3)

msg = Window(220,140, "")
msg.width = 200
msg.height = 200
msg.visible = false
hide_button = Button("New game", 80)
hide_button.x = 110
hide_button.y = 155
hide_button.onClick = function(self)
  msg.visible = false
  newGame()
end
msg:add(hide_button)


naught = Texture.loadTexture("naught.png", true)
cross = Texture.loadTexture("cross.png", true)

scene = Scene.get()

camera = scene:getCamera()
camera.rotX = 30
camera.rotY = -30

turn = 0

belongs = {}
placed = 0

function newGame()
  for i=1,9 do
    fields[i].color = field_color
    fields[i].textured = false
  end
  belongs = {}
  turn = 0
  placed = 0
  player.caption = "Player " .. (turn + 1)
end

function checkWinner()
  local winner = nil
  for i=0,2 do
    local j = i * 3 + 1
    if belongs[j] ~= nil and belongs[j] == belongs[j+1] and belongs[j] == belongs[j+2] then
      winner = belongs[j]
      break
    end
    if belongs[i+1] ~= nil and belongs[i+1] == belongs[i+4] and belongs[i+1] == belongs[i+7] then
      winner = belongs[i+1]
      break
    end
  end

  if winner == nil and (belongs[1] == belongs[5] and belongs[1] == belongs[9])
     or (belongs[3] == belongs[5] and belongs[3] == belongs[7]) then
    winner = belongs[5]
  end

  if placed == 9 then
    msg.title = "The game was a draw!"
    msg.visible = true
    return
  end

  if winner ~= nil then
    msg.title = "Winner is player " .. (winner + 1)
    msg.visible = true
--    resetBoard()
  end
end

function onClick(sel)
   if belongs[sel.id] == nil then
     placed = placed + 1
     belongs[sel.id] = turn
     if turn == 0 then
       sel.texture = cross
     else
       sel.texture = naught
     end
     sel.textured = true
     checkWinner()
     turn = 1 - turn
     player.caption = "Player " .. (turn + 1)
   end
end

fields = {}

obj = createQuad()
obj.pos = Point3f(0, -1.1, 0)
obj.scale = Point3f(3.2,3.2,3.2)
obj.color = Point4f(0, 0, 0.3, 1)
scene:add(obj)

for i=-1,1 do
   for j=-1,1 do
      obj = createQuad()
      obj.pos = Point3f(i*2.1,-1,j*2.1)
      obj.color = field_color
      obj.id = (i + 1) + (j + 1)*3 + 1
      obj.onClick = onClick
      fields[obj.id] = obj
      scene:add(obj)
   end
end

