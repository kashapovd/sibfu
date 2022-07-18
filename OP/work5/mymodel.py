# SPDX-FileCopyrightText: 2021 Kirill Pushkaryov <kpushkaryov@gmail.com>
#
# SPDX-License-Identifier: MIT
"""Optimal evasion example module."""
from evader.math import float_array
import evader.controller
import evader.objects


def get_model_objects(args=dict()):
    """Demonstrates an aircraft evading missiles.

    The aircraft tries to reach the target, while two missile systems try
    to shoot it down.

    Args:
        args: Optional; Arguments dictionary.
    """
    # Цель, куда стремится попасть летательный аппарат
    target = float_array([41, 0])
    solvers = {
        'none': None,
        'minfuel': evader.controller.EvasionSolverMinFuel(safe_dist=6),
        'maxnextdist': evader.controller.EvasionSolverMaxNextDist(),
        'maxmindist': evader.controller.EvasionSolverMaxMinDist()
    }
    solver_id = args.get('solver_id', 'none')
    solver = solvers[solver_id]
    if not solver:
        air_contr = evader.controller.AircraftControllerEvadingTargeted(
            aircraft=None,
            target=target
        )
    else:
        air_contr = evader.controller.AircraftControllerOptimalEvasion(
            aircraft=None,
            target=target,
            evasion_solver=solver
        )
    return [
        # Создаём экземпляр летательного аппарата
        evader.objects.Aircraft(
            x=float_array([18, 89]),  # Положение (x, y)
            v=float_array([2, 0]),  # Скорость
            vmax=20,  # Максимальная скорость
            dvmax=12,  # Максимальное ускорение
            controller=air_contr  # Контроллер
        ),
        # Создаём два экземпляра ракетной установки
        evader.objects.MissileSystem(
            x=float_array([10, 0]),  # Положение (x, y)
            v=float_array([0, 0]),  # Скорость
            missile_vmax=56,  # Максимальная скорость ракеты
            expl_range=7,  # Радиус поражения ракеты
            rate_of_fire=1,  # Скорострельность (задержка между пусками ракет)
            firing_range=42,  # Радиус захвата цели
            max_firing_angle=1.4,  # Максимальный угол отклонения от вертикали при пуске (в радианах)
            missile_factory=evader.objects.UnguidedMissile,  # Функция, производящая ракеты
            name='MissileSystem1'  # Имя установки
        ),
        evader.objects.MissileSystem(
            x=float_array([84, 0]),
            v=float_array([0, 0]),
            missile_vmax=59,
            expl_range=4,
            rate_of_fire=1,
            firing_range=57,
            max_firing_angle=1.5,
            missile_factory=evader.objects.UnguidedMissile,
            name='MissileSystem2'
        )
    ]
