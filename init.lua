sel = {}

myw = Window(200, 250, "Inspector")
myw.width = 160
myw.height = 100

tbx = TextBox(5, 25, 150, 20, "")
tby = TextBox(5, 48, 150, 20, "")

button = Button(55, 71, 100, 20, "Update")
button.onClick = function(self)
   p = points[sel.title]
   sel.x = tonumber(tbx.text)
   sel.y = tonumber(tby.text)
   sel:onMove()
end

myw:add(tbx)
myw:add(tby)
myw:add(button)


windows = {}

points = {}

nurb = Nurbs()

count = 0


-- Nurbs test:

function pointMove(self)
   if sel.title ~= self.title then
     sel = self
     myw.title = "Inspecting: " .. sel.title
   end
   p = points[self.title]
   p.x = self.x + self.width / 2
   p.y = self.y + self.height / 2

   tbx.text = "" .. self.x
   tby.text = "" .. self.y
end

for v=1,5 do
   count = count + 1
   i = count
   p = Point2D(50 + i * 100, 100)
   w = Window(50 + i * 100 - 5, 100 - 5, ""..i)
   w.onMove = pointMove
   windows[""..i] = w
   points[""..i] = p
   nurb:addPoint(p)
end

control = Window(30, 250, "Controls")
control.width = 150
control.height = 100

create_but = Button(10, 25, 100, 20, "Add point");
create_but.onClick = function(self)
   count = count + 1
   i = count
   p = Point2D(550, 200)
   w = Window(550 - 5, 200 - 5, ""..i)
   w.onMove = pointMove
   windows[""..i] = w
   points[""..i] = p
   nurb:addPoint(p)
end

exit_app = Button(10, 48, 100, 20, "Exit");
exit_app.onClick = function(self)
   System.exit(0)
end

control:add(create_but)
control:add(exit_app)