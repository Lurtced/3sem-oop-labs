This solution contains **all the labs of the 3rd semester** on OOP and QT (C++).

This is **one solution** containing several projects.
It is designed in **Visual Studio** hence recommended to run in it.

**Accepted** - 1, 2, 3, 5, 6

**Waiting to show** - 4

**Refactoring** - 7

See unfinished labs in separate branches.

*There may be some trash files, but the projects are working fine.*

___
# Вопросы и замечания
**2 лаба**
- Q: сколько объектов класса ```Shape``` создается при создании объектов разных классов?\\
(A: ```Vector``` - 1, ```Circle``` - 2, ```Rect```  - 3: некоторые содержат в себе еще и другие объекты
(как в круге есть точка, а в квадрате две точки))

**6 лаба**
- не надо удалять вручную связи: они удаляются автоматически при разрушении объекта
- на надо хранить связи в контейнере: есть метод для обращения к ним