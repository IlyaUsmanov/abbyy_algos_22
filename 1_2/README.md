Виртуальное наследование - механизм, позволяющий не создавать лишние экземпляры классов при некоторых видах множественного наследования(например, ромбовидного)
При виртуальном наследовании вместо экземпляра базового класса(A) в наследнике(B) сохраняется "указатель" на экземпляр базового класса общий для всей цепочки наследования, эти экземпляры лежат в памяти после всех остальных данных. Т.е., теперь A уже принадлежит не B, а самому нижнему в иерархии наследования классу(C), и как следствие, необходимо явно вызывать конструктор для A в C.