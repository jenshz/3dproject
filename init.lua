windows = {}

main_win = Window(0, 0, "Main Menu")
main_win.border = false
main_win.draggable = false

close_but = Button("Quit", 100)
close_but.onClick = function(self)
  os.exit()
end

windows[main_win] = true

main_win:add(close_but)
main_win:pack()


-- Game

scene = Scene.get()

camera = scene:getCamera()
camera.rotX = 30
camera.rotY = -30

lsel = {}

function onClick(sel)
   lsel.color = Point3f(0.3, 0.3, 0.3)
   lsel = sel
   sel.color = Point3f(1,0,0)
end

scene.onDeselect = function()
   lsel.color = Point3f(0.3, 0.3, 0.3)
end

for i=-1,1 do
   for j=-1,1 do
      obj = createQuad()
      obj.pos = Point3f(i*2.1,-1,j*2.1)
      obj.color = Point3f(0.3, 0.3, 0.3)
      obj.id = (i + 1) + (j + 1)*3 + 1
      obj.onClick = onClick
      scene:add(obj)
   end
end

