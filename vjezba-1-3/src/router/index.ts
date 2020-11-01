import { createRouter, createWebHistory, RouteRecordRaw } from 'vue-router'
import vjezba1sat from '../views/vjezba-1-sat.vue'
import vjezba1dizalo from '../views/vjezba-1-dizalo.vue'
import vjezba3 from '../views/vjezba-3.vue'

const routes: Array<RouteRecordRaw> = [
  {
    path: '/',
    name: 'vjezba-1-sat',
    component: vjezba1sat
  },
  {
    path: '/vjezba-1-dizalo',
    name: 'vjezba-1-dizalo',
    component: vjezba1dizalo
  },
  {
    path: '/vjezba-3',
    name: 'vjezba-3',
    component: vjezba3
  }
]

const router = createRouter({
  history: createWebHistory(process.env.BASE_URL),
  routes
})

export default router
