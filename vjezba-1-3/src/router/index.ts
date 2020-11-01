import { createRouter, createWebHistory, RouteRecordRaw } from 'vue-router'
import vjezba1 from '../views/vjezba-1.vue'
import vjezba3 from '../views/vjezba-3.vue'

const routes: Array<RouteRecordRaw> = [
  {
    path: '/',
    name: 'vjezba-1',
    component: vjezba1
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
