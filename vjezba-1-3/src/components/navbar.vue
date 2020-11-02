<template>
  <nav class="navbar sticky-top navbar-expand navbar-light navbar-general">
    <span class="navbar-logo"
      ><logo class="mr-3 mb-1" />PIIS 2020
      <span class="subtitle-text ml-2">Matija Novosel</span></span
    >
    <div class="collapse navbar-collapse">
      <ul class="navbar-nav mx-auto">
        <li class="nav-item mx-2" v-for="(item, i) in navigationLinks" :key="i">
          <span
            @click="redirect(item.name)"
            class="badge badge-pill pill shadow"
            :class="{ 'active-route': route.name == item.name }"
            >{{ item.title }}</span
          >
        </li>
      </ul>
    </div>
  </nav>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import { useRouter, useRoute } from "vue-router";
import logo from "@/components/logo.vue";

interface Route {
  name: string;
  title: string;
}

export default defineComponent({
  name: "navbar",
  components: {
    logo
  },
  setup() {
    const router = useRouter();
    const route = useRoute();

    const navigationLinks: Array<Route> = [
      {
        name: "vjezba-1-sat",
        title: "Vježba 1 - Sat"
      },
      {
        name: "vjezba-1-dizalo",
        title: "Vježba 1 - Dizalo"
      },
      {
        name: "vjezba-3",
        title: "Vježba 3"
      }
    ];

    function redirect(name: string) {
      router.push({ name });
    }

    return {
      redirect,
      route,
      navigationLinks
    };
  }
});
</script>

<style scoped>
.navbar-general {
  border-bottom: 1px solid var(--border-color-dark);
  height: var(--navbar-height);
  max-height: var(--navbar-height);
  box-shadow: 0px 3px 9px #888888;
  background-color: white;
}
.navbar-logo {
  position: absolute;
  left: 35px;
  top: 20px;
  font-size: 20px;
  color: #273849;
  font-family: "Dosis", "Source Sans Pro", "Helvetica Neue", Arial, sans-serif;
  font-weight: 500;
}
.subtitle-text {
  color: grey;
  font-size: 12px;
}
.pill {
  font-size: 12px;
  cursor: pointer;
  padding: 6px 12px;
  background-color: #273849;
  color: white;
  user-select: none;
}
.pill:hover {
  background-color: grey;
}
.active-route {
  background-color: var(--vue-logo-green);
}
</style>
