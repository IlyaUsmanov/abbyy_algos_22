Решим задачу рекурсивным перебором. На текущем шаге фиксированы число вершин(n) и значение в минимальной(start_val), тогда переберем все возможные значения в корне(start_val...start_val+n-1), для каждого значения(val) слева все дети должны быть меньше, а справа - больше, значит, чтобы получить все возможные деревья с текущим возможным значением в корне, нужно вызвать ту же функцию от (val-start_val, start_val)->получим левые поддеревья и (n+start_val-val-1, val+1)->получим правые поддеревья, возьмем их попарные комбинации, делая левым и правым сыном текущего значения соответсвенно. Затем объединим ответы для всех рассмотренных значений и вернем 