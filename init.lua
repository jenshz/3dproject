control = Window(10, 300, "Controls")
control.width = 400
control.height = 100
control.draggable = false

windows = {}

points = {}

nurb = Nurbs()

create_but = Window(13, 340, "Add point");
create_but.width = 100
create_but.height = 22
create_but.draggable = false

count = 0


-- Nurbs test:

function pointMove(self)
   p = points[self.title]
   p.x = self.x + self.width / 2
   p.y = self.y + self.height / 2
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
